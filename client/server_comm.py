import socket
#class for node data
class Node:
    def __init__(self, ip, port, encryption, keys):
        self.ip = ip
        self.port = port
        self.encryption = encryption
        self.keys = keys

def getPath():
