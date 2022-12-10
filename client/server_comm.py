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
        s.sendall(parse_request(150, ""))
        data = s.recv(1024)
        response = data[5:get_len(data)]

        #parse json and turn it in to routes

def get_len(msg):
    return int.from_bytes(msg[1:5], byteorder="big")
def parse_request(code, json):
    data = int(code).to_bytes(1, byteorder="big") + int(len(json)).to_bytes(4, byteorder="big") + json.encode()
    return data
