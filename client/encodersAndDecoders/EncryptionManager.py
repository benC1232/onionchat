from abc import ABC, abstractmethod


class EncryptionManager(ABC):
    @abstractmethod
    def encrypt(self, data):
        pass

    @abstractmethod
    def decrypt(self, data):
        pass
