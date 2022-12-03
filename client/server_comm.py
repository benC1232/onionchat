import socket
import json


# class for node data
class Node:
    def __init__(self, ip, port, encryption, keys):
        self.ip = ip
        self.port = port
        self.encryption = encryption
        self.keys = keys


def get_path():
    # this line makes the scope not mess up the dict, do not change
    server_settings = {}
    with open("settings.json", "r") as json_file:
        server_settings = json.load(json_file)['server_settings']
    HOST = server_settings['server_ip']
    PORT = server_settings['server_port']
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(parse_request(210, ""))
        data = s.recv(1024)
        # TODO: process json response from server


def parse_request(code, json):
    data = int(code).to_bytes(1, byteorder="big") + int(len(json)).to_bytes(4, byteorder="big") + json.encode()
    return data
