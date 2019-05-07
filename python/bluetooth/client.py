#!/usr/bin/env python3

import socket

server = '00:1f:e1:dd:08:3d'
port = 3

s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
s.connect((server, port))

while 1:
    text = input()
    if text == "quit":
        break
    s.send(bytes(text, 'UTF-8'))

s.close()

