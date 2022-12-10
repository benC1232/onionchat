import socket
import server_comm

def build_request(nodes, dest, content):
    msg = bytes()
    for node in nodes[1:]:
        ip_bytes = socket.inet_aton(node.ip)
        port_bytes = node.port.to_bytes(2,'big')
        msg+=ip_bytes+port_bytes
    dest_bytes = socket.inet_aton(dest[0])+dest[1].to_bytes(2,'big')
    msg = len(content).to_bytes(4, 'big') + msg + dest_bytes + content.encode()
    return msg

