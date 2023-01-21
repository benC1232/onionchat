from Crypto import Random
from Crypto.Cipher import AES

from EncryptionManager import EncryptionManager
from AESManager import AESManager


from tinyec import registry
from Crypto.Cipher import AES
import hashlib, secrets, binascii


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
class ECCManager(EncryptionManager):
    def __init__(self,curve):
        self._curve = curve

    def encrypt(self, data, pubKey):
        ciphertextPrivateKey = secrets.randbelow(self._curve.field.n)
        sharedECCKey = ciphertextPrivateKey * pubKey
        secretKey = ecc_point_to_256_bit_key(sharedECCKey)
        ciphertext, nonce, authTag = encrypt_AES_GCM(data, secretKey)
        ciphertextPubKey = ciphertextPrivateKey * self._curve.g
        return ciphertext, nonce, authTag, ciphertextPubKey

    def decrypt(self, data, privKey):
        ciphertext, nonce, authTag, ciphertextPubKey = data
        sharedECCKey = privKey * ciphertextPubKey
        secretKey = ecc_point_to_256_bit_key(sharedECCKey)
        plaintext = decrypt_AES_GCM(ciphertext, nonce, authTag, secretKey)
        return plaintext

    @property
    def curve(self):
        return self._curve


msg = b'Hello World'
print(f'Original data: {msg}')
ecc = ECCManager(registry.get_curve('brainpoolP256r1'))
privateKey = secrets.randbelow(ecc._curve.field.n)
publicKey = privateKey * ecc.curve.g
print(f'Public key: {publicKey}')
ciphertext, nonce, authTag, ciphertextPubKey = ecc.encrypt(msg, publicKey)
print(f'Ciphertext: {ciphertext}')
print(f'Nonce: {nonce}')
print(f'AuthTag: {authTag}')
print(f'Ciphertext public key: {ciphertextPubKey}')
plaintext = ecc.decrypt((ciphertext, nonce, authTag, ciphertextPubKey), privateKey)
print(f'Plaintext: {plaintext}')







