'''
Copyright 2017 Ford Motor Company

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

 3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
'''

from asyncore import dispatcher_with_send
import logging
import socket
import sys


def create(socket):
    '''Creates new connection

    Args:
        socket : TBD 
    '''
    return BluetoothConnection(socket)


class BluetoothConnection(dispatcher_with_send):
    '''Represents a client connection with SDL'''
    __logger = logging.getLogger('route')

    def __init__(self, socket):
        '''Constructor

        Args:
            socket : TBD
        '''
        dispatcher_with_send.__init__(self)
        self.__peer = None
        self.set_socket(socket)

    def __eq__(self, other):
        # pylint: disable=protected-access
        # return self.__host == other.__host and self.__port == other.__port
        return "Bluetooth connection"

    def __str__(self):
        # return "%s:%i" % (self.__host, self.__port)
        pass

    def link(self, peer):
        '''Links peer

        Args:
            peer: routing.Connection instance
        '''
        self.__peer = peer

#    def open(self, credentials=None):
#        '''Connects to server
#
#        Args:
#            credentials: optional dictionary of credentials, for example:
#
#            {'vin': "vin123", 'token': "token123"}
#        '''
#        self.__credentials = credentials
#        self.create_socket(socket.AF_INET, socket.SOCK_STREAM)
#        try:
#            self.connect((self.__host, self.__port))
#        except OSError as error:
#            self.__logger.warning('Could not connect to %s %s', self, error)

#    def handle_connect(self):
#        self.__logger.info("Connected to %s", self)
#        if self.__credentials:
#            self.send(json.dumps(self.__credentials).encode())

    def handle_close(self):
        self.__logger.info("Closed %s", self)
        self.close()
        if self.__peer.connected:
            self.__peer.close()

    def handle_error(self):
        error = sys.exc_info()[1]
        self.__logger.error("Could not connect to %s %s", self, error)

    def handle_read(self):
        data = self.recv(8192)
        if data:
            self.__logger.debug(
                "Transfer %s -> %s data=%s", self, self.__peer, data)
            self.__peer.send(data)
