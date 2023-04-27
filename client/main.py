import server_comm
import socket
import routing
import json
def main():
    nodes = server_comm.get_path()
    with open("settings.json", "r") as json_file:
        dest_settings = json.load(json_file)['dest_settings']
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((nodes[0].ip, nodes[0].port))
        while True:
            s.sendall(routing.build_request(nodes, (dest_settings['dest_ip'],dest_settings['dest_port']), input("enter message:")))
            data = s.recv(1024)

if __name__ == '__main__':
    main()
