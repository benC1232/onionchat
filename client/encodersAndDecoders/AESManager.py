from EncryptionManager import EncryptionManager
import base64
from Crypto.Cipher import AES
from Crypto import Random


class AESManager(EncryptionManager):
    def __init__(self, key):
        self._key = key

    def encrypt(self, data):
        iv = Random.new().read(AES.block_size)
        cipher = AES.new(self._key, AES.MODE_CFB, iv)
        return base64.b64encode(iv + cipher.encrypt(data))

    def decrypt(self, data):
        data = base64.b64decode(data)
        iv = data[:AES.block_size]
        cipher = AES.new(self._key, AES.MODE_CFB, iv)
        return cipher.decrypt(data[AES.block_size:])


def generate_key():
    return Random.new().read(AES.block_size)


if __name__ == '__main__':
    key = generate_key()
    aes = AESManager(key)
    data_to_test = 'Hello World'
    print(f'Original data: {data_to_test}')
    print(f'Key: {key}')
    encrypted = aes.encrypt(data_to_test.encode())
    print(encrypted)
    decrypted = aes.decrypt(encrypted).decode()
    print(decrypted)
