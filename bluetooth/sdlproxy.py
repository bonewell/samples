#!/usr/bin/env python3

import bluetooth

host = '00:1b:dc:06:d8:37'
#host = ""
#port = 9
port = bluetooth.PORT_ANY

backlog = 1
size = 1024
s = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
s.bind((host, port))
s.listen(backlog)

#port = server_sock.getsockname()[1]

#uuid = "94f39d29-7d6d-437d-973b-fba39e49d4ee"
uuid = "936da01f-9abd-4d9d-80c7-02af85c822a8"

bluetooth.advertise_service(s, "SdlProxy",
    service_id = uuid,
    service_classes = [ uuid ],
#    profiles = [ bluetooth.SERIAL_PORT_PROFILE,
#                 bluetooth.HEADSET_AGW_PROFILE,
#                 bluetooth.HANDSFREE_AGW_PROFILE ],
#    protocols = [ bluetooth.OBEX_UUID ] 
)

try:
    client, clientInfo = s.accept()
    print("Connection is accepted")
    while 1:
        data = client.recv(size)
        if data:
            print(data)
            client.send(data)
except Exception as error:
    print(error)
    print("Closing socket")
    client.close()
    s.close()

