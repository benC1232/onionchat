import math
import random
from abc import ABC

from tinyec import registry
from Crypto.Cipher import AES
import hashlib, secrets, binascii
import EncryptionManager


def encrypt_AES_GCM(msg, secretKey):
    aesCipher = AES.new(secretKey, AES.MODE_GCM)
    ciphertext, authTag = aesCipher.encrypt_and_digest(msg)
    return ciphertext, aesCipher.nonce, authTag


def decrypt_AES_GCM(ciphertext, nonce, authTag, secretKey):
    aesCipher = AES.new(secretKey, AES.MODE_GCM, nonce)
    plaintext = aesCipher.decrypt_and_verify(ciphertext, authTag)
    return plaintext


def ecc_point_to_256_bit_key(point):
    sha = hashlib.sha256(int.to_bytes(point.x, 32, 'big'))
    sha.update(int.to_bytes(point.y, 32, 'big'))
    return sha.digest()


class ECCManager(EncryptionManager.EncryptionManager, ABC):
    def __init__(self, curve):
        self.curve = curve;

    # in encryption the key is the pubKey
    def encrypt(self, data, key):
        ciphertextPrivKey = secrets.randbelow(self.curve.field.n)
        sharedECCKey = ciphertextPrivKey * key
        secretKey = ecc_point_to_256_bit_key(sharedECCKey)
        ciphertext, nonce, authTag = encrypt_AES_GCM(data, secretKey)
        ciphertextPubKey = ciphertextPrivKey * self.curve.g
        return ciphertext, nonce, authTag, ciphertextPubKey

    def decrypt(self, data, key):
        (ciphertext, nonce, authTag, ciphertextPubKey) = data
        sharedECCKey = key * ciphertextPubKey
        secretKey = ecc_point_to_256_bit_key(sharedECCKey)
        plaintext = decrypt_AES_GCM(ciphertext, nonce, authTag, secretKey)
        return plaintext


def cipherTupleToDict(cipherTuple):
    return {
        'ciphertext': binascii.hexlify(cipherTuple[0]),
        'nonce': binascii.hexlify(cipherTuple[1]),
        'authTag': binascii.hexlify(cipherTuple[2]),
        'ciphertextPubKey': hex(cipherTuple[3].x) + hex(cipherTuple[3].y % 2)[2:]
    }


def DictToCipherTuple(cipherDict):
    return (
        binascii.unhexlify(cipherDict['ciphertext']),
        binascii.unhexlify(cipherDict['nonce']),
        binascii.unhexlify(cipherDict['authTag']),
        registry.get_curve('brainpoolP256r1')
    )


if __name__ == '__main__':
    cur = registry.get_curve('brainpoolP256r1')
    msg = b'Text to be encrypted by ECC public key and ' \
          b'decrypted by its corresponding ECC private key'
    print("original msg:", msg)
    privKey = secrets.randbelow(cur.field.n)
    pubKey = privKey * cur.g
    ecc = ECCManager(cur)
    encryptedMsg = ecc.encrypt(msg, pubKey)
    encryptedMsgObj = cipherTupleToDict(encryptedMsg)
    print("encrypted msg:", encryptedMsgObj)

    encryptedMsg = DictToCipherTuple(encryptedMsgObj)
    decryptedMsg = ecc.decrypt(encryptedMsg, privKey)
    print("decrypted msg:", decryptedMsg)
