import hashlib

from Crypto import Random
from Crypto.Cipher import AES
import base64
import math
import random


def generate_AES_key():
    """
    Generates a random 256-bit AES key.
    :return: A random 256-bit AES key.
    :rtype: bytes
    """
    return Random.new().read(AES.block_size)


def encrypt_AES_GCM(msg, secretKey):
    """
    Encrypts a message using AES in GCM mode.
    :param msg: The message to encrypt.
    :param secretKey:  The secret key to use for encryption.
    :type secretKey: bytes
    :type msg: bytes
    :return: A tuple containing the ciphertext, nonce, and authentication tag.
    :rtype: tuple
    """
    aesCipher = AES.new(secretKey, AES.MODE_GCM)
    ciphertext, authTag = aesCipher.encrypt_and_digest(msg)
    return ciphertext, aesCipher.nonce, authTag


def decrypt_AES_GCM(ciphertext, nonce, authTag, secretKey):
    """
    Decrypts a message using AES in GCM mode.
    :param ciphertext: The ciphertext to decrypt.
    :param nonce: The nonce to use for decryption. (nonce is a random number used only once)
    :param authTag: The authentication tag to use for decryption.
    :param secretKey: The secret key to use for decryption.
    :type secretKey: bytes
    :type ciphertext: bytes
    :type nonce: bytes
    :type authTag: bytes
    :return: The decrypted message.
    :rtype: bytes
    """
    aesCipher = AES.new(secretKey, AES.MODE_GCM, nonce)
    plaintext = aesCipher.decrypt_and_verify(ciphertext, authTag)
    return plaintext


def ecc_point_to_256_bit_key(point):
    """
    Converts an ECC point to a 256-bit key.
    :param point: The ECC point to convert.
    :type point: Point
    :return: The 256-bit key.
    :rtype: bytes
    """
    sha = hashlib.sha256(int.to_bytes(point.x, 32, 'big'))
    sha.update(int.to_bytes(point.y, 32, 'big'))
    return sha.digest()


def gcd(a, b):
    """
    Calculates the greatest common divisor of two numbers.
    :param a: The first number.
    :param b: The second number.
    :type a: int
    :type b: int
    :return: The greatest common divisor of a and b.
    :rtype: int
    """
    while b != 0:
        a, b = b, a % b
    return a


def mod_inverse(a, m):
    """
    Calculates the modular multiplicative inverse of a number.
    :param a: The number to calculate the inverse of.
    :param m: The modulus.
    :type a: int
    :type m: int
    :return: The modular multiplicative inverse of a.
    :rtype: int
    """
    for x in range(1, m):
        if (a * x) % m == 1:
            return x
    return -1


def is_prime(n):
    """
    Checks if a number is prime.
    :param n: The number to check.
    :type n: int
    :return: True if n is prime, False otherwise.
    :rtype: bool
    """
    if n < 2:
        return False
    elif n == 2:
        return True
    else:
        for i in range(2, int(math.sqrt(n)) + 1, 2):
            if n % i == 0:
                return False
    return True


def getClosestPrime(num):
    """
    Gets the closest prime number to the given number.
    :param num: The number to get the closest prime to.
    :type num: int
    :return: The closest prime number to num.
    :rtype: int
    """
    if num % 2 == 0:
        num += 1
    while not is_prime(num):
        num += 2
    return num

def generate_RSA_keypair(p, q) -> tuple[tuple[int, int], tuple[int, int]]:
    """
    Generates an RSA keypair.
    :param p: The first prime number.
    :param q: The second prime number.
    :param key_size: The size of the key to generate.
    :type p: int
    :type q: int
    :return: A tuple containing the public key and private key.
    :rtype: tuple
    """

    if not (is_prime(p) and is_prime(q)):
        raise ValueError('Both numbers must be prime.')
    elif p == q:
        raise ValueError('p and q cannot be equal')
    n = p * q
    phi = (p - 1) * (q - 1)
    e = random.randrange(1, phi)
    g = gcd(e, phi)
    while g != 1:
        e = random.randrange(1, phi)
        g = gcd(e, phi)
    d = mod_inverse(e, phi)
    return ((e, n), (d, n))

