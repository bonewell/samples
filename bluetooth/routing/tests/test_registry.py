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
from unittest.mock import call
import asyncore
import imp
from core import Config
from routing import connection
from routing import Registry
from routing import route


class Test(unittest.TestCase):
    config = None

    def setUp(self):
        self.config = Config()
        self.config.sdl_host = Mock(return_value="127.0.0.1")
        self.config.sdl_port = Mock(return_value=12345)
        self.config.vin = Mock(return_value="vin123")
        self.config.timeout = Mock(return_value=60)

    def tearDown(self):
        imp.reload(asyncore)
        imp.reload(route)
        imp.reload(connection)

    def test_add(self):
        connection.create = Mock(side_effect=[1, 2])
        way = Mock()
        way.start = Mock()
        route.create = Mock(return_value=way)
        registry = Registry(self.config)
        self.assertIsNone(registry.add({'host': "127.0.0.2", 'port': 80}))
        calls = [call("127.0.0.2", 80), call("127.0.0.1", 12345)]
        connection.create.assert_has_calls(calls)
        route.create.assert_called_once_with(1, 2)
        way.start.assert_called_once_with()

    def test_add_two(self):
        connection.create = Mock(side_effect=[1, 2, 3, 4])
        way1 = Mock()
        way1.start = Mock()
        way2 = Mock()
        way2.start = Mock()
        route.create = Mock(side_effect=[way1, way2])
        registry = Registry(self.config)
        self.assertIsNone(registry.add({'host': "127.0.0.2", 'port': 80}))
        self.assertIsNone(registry.add({'host': "127.0.0.3", 'port': 81}))
        calls = [call("127.0.0.2", 80), call("127.0.0.1", 12345),
                 call("127.0.0.3", 81), call("127.0.0.1", 12345)]
        connection.create.assert_has_calls(calls)
        calls_way = [call(1, 2), call(3, 4)]
        route.create.assert_has_calls(calls_way)
        way1.start.assert_called_once_with()
        way2.start.assert_called_once_with()

    def test_add_the_same(self):
        connection.create = Mock(side_effect=[1, 2])
        way = Mock()
        way.start = Mock()
        route.create = Mock(return_value=way)
        registry = Registry(self.config)
        self.assertIsNone(registry.add({'host': "127.0.0.2", 'port': 80}))
        self.assertIsNone(registry.add({'host': "127.0.0.2", 'port': 80}))
        calls = [call("127.0.0.2", 80), call("127.0.0.1", 12345)]
        connection.create.assert_has_calls(calls)
        route.create.assert_called_once_with(1, 2)
        way.start.assert_called_once_with()

    def test_add_incorect_address(self):
        connection.create = Mock()
        way = Mock()
        way.start = Mock()
        route.create = Mock(return_value=way)
        registry = Registry(self.config)
        self.assertIsNone(registry.add({'host': "127.0.0.2", 'port': "abc"}))
        route.create.assert_not_called()
        way.start.assert_not_called()

    def test_add_with_token(self):
        connection.create = Mock(side_effect=[1, 2])
        way = Mock()
        way.start = Mock()
        route.create = Mock(return_value=way)
        registry = Registry(self.config)
        self.assertIsNone(registry.add(
            {'host': "127.0.0.2", 'port': 80, 'token': "token123"}))
        calls = [call("127.0.0.2", 80), call("127.0.0.1", 12345)]
        connection.create.assert_has_calls(calls)
        route.create.assert_called_once_with(1, 2)
        way.start.assert_called_once_with(
            {'vin': "vin123", 'token': "token123"})

    def test_stop(self):
        registry = Registry(self.config)
        registry._Registry__running = True
        registry._Registry__routes = {'1': 1, '2': 2}
        self.assertTrue(registry.running())
        self.assertTrue(registry._Registry__routes)
        self.assertIsNone(registry.stop())
        self.assertFalse(registry.running())
        self.assertFalse(registry._Registry__routes)

    def test_stop_zero(self):
        registry = Registry(self.config)
        self.assertIsNone(registry.stop())
        self.assertFalse(registry.running())
        self.assertFalse(registry._Registry__routes)

    def test_loop(self):
        asyncore.loop = Mock()
        registry = Registry(self.config)
        registry.running = Mock(side_effect=[True, False])
        self.assertIsNone(registry.loop())
        self.assertEqual(2, registry.running.call_count)
        asyncore.loop.assert_called_once_with()

    def test_loop_timeout(self):
        asyncore.loop = Mock()
        config = Config()
        config.timeout = Mock(return_value=10)
        registry = Registry(config)
        registry.running = Mock(side_effect=[True, False])
        self.assertIsNone(registry.loop())
        self.assertEqual(2, registry.running.call_count)
        asyncore.loop.assert_called_once_with(timeout=10)

    def test_get_info(self):
        registry = Registry(self.config)
        self.assertEqual((None, None, None, True), registry.get_info({}))
        self.assertEqual((None, None, None, True),
                         registry.get_info({'host': "127.0.0.1"}))
        self.assertEqual((None, None, None, True),
                         registry.get_info({'port': 80}))
        self.assertEqual((None, None, None, True),
                         registry.get_info({'host': "", 'port': 80}))
        self.assertEqual((None, None, None, True), registry.get_info(
            {'host': "127.0.0.1", 'port': "abc"}))
        self.assertEqual(("127.0.0.1", 1234, None, False), registry.get_info(
            {'host': "127.0.0.1", 'port': 1234}))
        self.assertEqual(("127.0.0.1", 1234, "token123", False), registry.get_info(
            {'host': "127.0.0.1", 'port': 1234, 'token': "token123"}))

    def test_refresh(self):
        registry = Registry(self.config)
        way = Mock()
        way.running = Mock(return_value=False)
        registry._Registry__routes = {'1': way}
        registry.refresh()
        self.assertFalse(registry._Registry__routes)


if __name__ == "__main__":
    unittest.main()
