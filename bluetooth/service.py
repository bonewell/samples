#!/usr/bin/env python3

import bluetooth

host = '00:1f:e1:dd:08:3d'
#host = ""
port = 3
#port = bluetooth.PORT_ANY

backlog = 1
size = 1024
s = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
s.bind((host, port))
s.listen(backlog)

#port = server_sock.getsockname()[1]

uuid = "94f39d29-7d6d-437d-973b-fba39e49d4ee"

bluetooth.advertise_service(s, "SampleServer",
    service_id = uuid,
    service_classes = [ uuid, bluetooth.SERIAL_PORT_CLASS ],
    profiles = [ bluetooth.SERIAL_PORT_PROFILE ],
#    protocols = [ bluetooth.OBEX_UUID ] 
)
try:
    client, clientInfo = s.accept()
    while 1:
        data = client.recv(size)
        if data:
            print(data)
            client.send(data)
except:
    print("Closing socket")
    client.close()
    s.close()

