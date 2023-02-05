package encodersAndDecoders

/*
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

import pickle

def to_bytes(data):
    return pickle.dumps(data)

def from_bytes(data):
    return pickle.loads(data)

# Encryption
data = b"example data"
key = some_elliptic_curve_key
enc_data = ECCManager.encrypt(data, key)
enc_data_bytes = to_bytes(enc_data)

# Decryption
dec_data = from_bytes(enc_data_bytes)
dec_data = ECCManager.decrypt(dec_data, key)

*/
