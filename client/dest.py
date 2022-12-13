import socket
import json
HOST = "127.0.0.1"

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    with open("settings.json", "r") as json_file:
        dest_settings = json.load(json_file)['dest_settings']
    s.bind((HOST, dest_settings['dest_port']))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print(f"Connected by {addr}")
        while True:
            data = conn.recv(1024)
            conn.sendall(input("enter message: ").encode())
