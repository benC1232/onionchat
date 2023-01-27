import math
import random


class ECCrypto:
    def __init__(self, public_key, private_key):
        self.public_key = public_key
        self.private_key = private_key
        self.curve = self.public_key['curve']
        self.generator = self.public_key['generator']
        self.prime = self.curve['prime']

    def encrypt(self, message):
        k = random.randrange(1, self.prime)
        k_inv = self._modinv(k, self.prime)
        x, y = self.generator
        x1, y1 = (x * k) % self.prime, (y * k) % self.prime
        x2, y2 = self.public_key['point']
        x3, y3 = (x1 + x2) % self.prime, (y1 + y2) % self.prime
        return x3, y3, message * k_inv % self.prime

    def decrypt(self, ciphertext):
        k = random.randrange(1, self.prime)

        x3, y3, c = ciphertext
        x1, y1 = (x3 * self.private_key) % self.prime, (y3 * self.private_key) % self.prime
        x2, y2 = self.generator
        x, y = (x1 - x2) % self.prime, (y1 - y2) % self.prime
        return c * self._modinv(k, self.prime) % self.prime

    def _modinv(self, a, m):
        g, x, _ = self._egcd(a, m)
        if g != 1:
            raise Exception("Modular inverse does not exist")
        else:
            return x % m

    def _egcd(self, a, b):
        if a == 0:
            return b, 0, 1
        else:
            g, y, x = self._egcd(b % a, a)
            return g, x - (b // a) * y, y


