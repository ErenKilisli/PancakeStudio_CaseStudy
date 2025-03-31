# udp_listener.py

import socket

print("Initializing UDP Listener...")

# Create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind to localhost and port 8888
sock.bind(("127.0.0.1", 8888))

print("Listening for UDP packets on 127.0.0.1:8888")

while True:
    data, addr = sock.recvfrom(1024)
    print("Received:", data.decode())

# make sure you have the python on your computer for check, write:
#     python --version

# Open a terminal and run:
# python udp_listener.py

# On macOS, if python doesn’t work, try:
# python3 udp_listener.py
