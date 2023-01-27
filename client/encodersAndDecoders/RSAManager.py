from EncryptionManager import EncryptionManager
import base64
import math
import random
from utils import generate_RSA_keypair as generate_keypair, getClosestPrime


class RSAManager(EncryptionManager):
    def __init__(self):
        print('creating RSA object')

    def encrypt(self, data: str, package: tuple[int,int]) -> list[int]:
        """
        Encrypts a string using RSA.
        :param data: The string to encrypt.
        :param package: The public key.
        :type data: str
        :type package: tuple
        :return: The encrypted string.
        :rtype: list
        """
        e, n = package
        return [pow(ord(char), e, n) for char in data]

    def decrypt(self, data: list[int], package: tuple[int,int]) -> str:
        """
        Decrypts a string using RSA.
        :param data: The string to decrypt.
        :param package: The private key.
        :type data: list
        :type package: tuple
        :return: The decrypted string.
        :rtype: str
        """
        d, n = package
        return ''.join([chr(pow(char, d, n)) for char in data])


if __name__ == '__main__':
    p,q = getClosestPrime(random.randint(100,1000)), getClosestPrime(random.randint(100,1000))
    print(f'p: {p}, q: {q}')
    public_key, private_key = generate_keypair(p, q)
    print(f'Public key: {public_key}')
    print(f'Private key: {private_key}')
    rsa = RSAManager()
    data_to_test = 'Hello World'
    print(f'Original data: {data_to_test}')
    encrypted = rsa.encrypt(data_to_test, public_key)
    print(f'Encrypted data: {encrypted}')
    decrypted = rsa.decrypt(encrypted, private_key)
    print(f'Decrypted data: {decrypted}')


