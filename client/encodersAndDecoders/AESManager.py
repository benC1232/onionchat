from EncryptionManager import EncryptionManager
import base64
from Crypto.Cipher import AES
from Crypto import Random
from utils import generate_AES_key as generate_key


class AESManager(EncryptionManager):
    def __init__(self):
        pass

    def encrypt(self, data, key):
        iv = Random.new().read(AES.block_size)
        cipher = AES.new(key, AES.MODE_CFB, iv)
        return base64.b64encode(iv + cipher.encrypt(data))

    def decrypt(self, data, key):
        data = base64.b64decode(data)
        iv = data[:AES.block_size]
        cipher = AES.new(key, AES.MODE_CFB, iv)
        return cipher.decrypt(data[AES.block_size:])


if __name__ == '__main__':
    keyAES = generate_key()
    aes = AESManager()
    data_to_test = 'Hello World'
    print(f'Original data: {data_to_test}')
    print(f'Key: {keyAES}')
    encrypted = aes.encrypt(data_to_test.encode(), keyAES)
    print(encrypted.decode())
    decrypted = aes.decrypt(encrypted, keyAES).decode()
    print(decrypted)
