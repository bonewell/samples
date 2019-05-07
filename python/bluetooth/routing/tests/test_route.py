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

# pylint: disable=missing-docstring
import unittest
from unittest.mock import Mock
from unittest.mock import MagicMock
from unittest.mock import PropertyMock
from routing import Route
from routing.route import create


class Test(unittest.TestCase):
    def test_create(self):
        app = Mock()
        app.link = Mock()
        app.open = Mock()
        sdl = Mock()
        sdl.link = Mock()
        sdl.open = Mock()
        self.assertEqual(Route(app, sdl), create(app, sdl))

    def test_start(self):
        app = Mock()
        app.link = Mock()
        app.open = Mock()
        sdl = Mock()
        sdl.link = Mock()
        sdl.open = Mock()
        route = Route(app, sdl)
        self.assertIsNone(route.start())
        app.link.assert_called_once_with(sdl)
        app.open.assert_called_once_with(None)
        sdl.link.assert_called_once_with(app)
        sdl.open.assert_called_once_with()

    def test_start_credentials(self):
        app = Mock()
        app.link = Mock()
        app.open = Mock()
        sdl = Mock()
        sdl.link = Mock()
        sdl.open = Mock()
        route = Route(app, sdl)
        self.assertIsNone(route.start({'vin': "vin123", 'token': "token123"}))
        app.link.assert_called_once_with(sdl)
        app.open.assert_called_once_with(
            {'vin': "vin123", 'token': "token123"})
        sdl.link.assert_called_once_with(app)
        sdl.open.assert_called_once_with()

    def test_stop(self):
        app = Mock()
        app.close = Mock()
        sdl = Mock()
        sdl.close = Mock()
        route = Route(app, sdl)
        self.assertIsNone(route.stop())
        app.close.assert_called_once_with()
        sdl.close.assert_called_once_with()

    def test_str(self):
        conn1 = Mock()
        conn1.__str__ = Mock(return_value="127.0.0.1:80")
        conn1.link = Mock()
        conn2 = Mock()
        conn2.__str__ = Mock(return_value="127.0.0.2:8080")
        conn2.link = Mock()
        route = Route(conn1, conn2)
        self.assertEqual("127.0.0.1:80 <=> 127.0.0.2:8080", "%s" % route)

    def test_eq(self):
        conn1 = Mock()
        conn2 = Mock()
        conn3 = Mock()
        conn4 = Mock()
        route1 = Route(conn1, conn2)
        route2 = Route(conn1, conn2)
        route3 = Route(conn3, conn4)
        route4 = Route(conn1, conn4)
        self.assertEqual(route1, route2)
        self.assertNotEqual(route2, route3)
        self.assertNotEqual(route3, route4)
        self.assertNotEqual(route2, route4)

    def test_running(self):
        conn1 = MagicMock()
        propertry1 = PropertyMock(side_effect=[True, True, False, False])
        type(conn1).connected = propertry1
        conn2 = MagicMock()
        propertry2 = PropertyMock(side_effect=[True, False, False, False])
        type(conn2).connected = propertry2
        route = Route(conn1, conn2)
        self.assertTrue(route.running())
        self.assertFalse(route.running())
        self.assertFalse(route.running())
        self.assertFalse(route.running())


if __name__ == "__main__":
    unittest.main()
