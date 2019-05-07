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

# pylint: disable=missing-docstring,protected-access
import unittest
from unittest.mock import Mock
import imp
import json
import sys
from routing import Connection
from routing.connection import create


class Test(unittest.TestCase):
    def test_create(self):
        self.assertEqual(Connection("127.0.0.3", 81), create("127.0.0.3", 81))

    def test_open(self):
        conn = Connection("127.0.0.3", 81)
        conn.connect = Mock()
        self.assertIsNone(conn.open())
        conn.connect.assert_called_once_with(("127.0.0.3", 81))

    def test_open_exception(self):
        conn = Connection("127.0.0.3", 81)
        conn.connect = Mock(side_effect=OSError)
        self.assertIsNone(conn.open())
        conn.connect.assert_called_once_with(("127.0.0.3", 81))

    def test_handle_connect(self):
        conn = Connection("127.0.0.3", 81)
        conn.send = Mock()
        self.assertIsNone(conn.handle_connect())
        credentials = {'vin': "vin123", 'token': "token123"}
        conn._Connection__credentials = credentials
        self.assertIsNone(conn.handle_connect())
        self.assertEqual(1, conn.send.call_count)
        self.assertEqual(credentials, json.loads(
            conn.send.mock_calls[0][1][0].decode()))

    def test_handle_close(self):
        peer = Connection("127.0.0.1", 80)
        peer.close = Mock()
        conn = Connection("127.0.0.3", 81)
        conn.close = Mock()
        self.assertIsNone(conn.link(peer))
        self.assertIsNone(conn.handle_close())
        conn.close.assert_called_once_with()
        peer.close.assert_not_called()

    def test_handle_close_and_peer(self):
        peer = Connection("127.0.0.1", 80)
        peer.close = Mock()
        peer.connected = True
        conn = Connection("127.0.0.3", 81)
        conn.close = Mock()
        self.assertIsNone(conn.link(peer))
        self.assertIsNone(conn.handle_close())
        conn.close.assert_called_once_with()
        peer.close.assert_called_once_with()

    def test_handle_error(self):
        conn = Connection("127.0.0.3", 81)
        sys.exc_info = Mock(return_value=("Type", "Value", "Traceback"))
        self.assertIsNone(conn.handle_error())
        sys.exc_info.assert_called_once_with()
        imp.reload(sys)

    def test_handle_read(self):
        peer = Connection("127.0.0.1", 80)
        peer.send = Mock()
        conn = Connection("127.0.0.3", 81)
        conn.recv = Mock(return_value=b"a1b2c3\n")
        self.assertIsNone(conn.link(peer))
        self.assertIsNone(conn.handle_read())
        conn.recv.assert_called_once_with(8192)
        peer.send.assert_called_once_with(b"a1b2c3\n")

    def test_handle_read_no_data(self):
        peer = Connection("127.0.0.1", 80)
        peer.send = Mock()
        conn = Connection("127.0.0.3", 81)
        conn.recv = Mock(return_value=b"")
        self.assertIsNone(conn.link(peer))
        self.assertIsNone(conn.handle_read())
        conn.recv.assert_called_once_with(8192)
        peer.send.assert_not_called()

    def test_str(self):
        conn = Connection("127.0.0.3", 81)
        self.assertEqual('127.0.0.3:81', "%s" % conn)

    def test_eq(self):
        conn1 = Connection("127.0.0.3", 81)
        conn2 = Connection("127.0.0.3", 81)
        conn3 = Connection("127.0.0.1", 80)
        conn4 = Connection("127.0.0.1", 81)
        self.assertEqual(conn1, conn2)
        self.assertNotEqual(conn1, conn3)
        self.assertNotEqual(conn3, conn4)
        self.assertNotEqual(conn2, conn4)


if __name__ == "__main__":
    unittest.main()
