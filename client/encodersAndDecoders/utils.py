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

