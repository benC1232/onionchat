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
        settings = json.load(json_file)

    HOST = settings['server_settings']['server_ip']
    PORT = settings['server_settings']['server_port']
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(parse_request(150, json.dumps(settings['path_settings'])))
        data = s.recv(1024)
        print(data)
        response = data[5:get_len(data)+5]
        return parse_response(response)


def get_len(msg):
    return int.from_bytes(msg[1:5], byteorder="big")
def parse_request(code, json):
    data = int(code).to_bytes(1, byteorder="big") + int(len(json)).to_bytes(4, byteorder="big") + json.encode()
    return data
def parse_response(msg):
    loaded_msg = json.loads(msg.decode())['route']['node1']
    node_list = []
    node_list.append(Node(loaded_msg['ip'],loaded_msg['port'],loaded_msg['encryption'],0))
    return node_list
