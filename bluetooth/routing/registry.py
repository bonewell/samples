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

import logging
import asyncore
from routing import route
from routing import connection


class Registry(object):
    '''Registry of routes'''
    __logger = logging.getLogger('core')

    def __init__(self, config):
        '''Constructor

        Args:
            config: core.Config instance
        '''
        self.__routes = {}
        self.__config = config
        self.__running = True

    def get_info(self, params):
        '''Gets fields like tuple from dictionary

        Args:
            params : dictionary of parameters of application, for example:

            {'host' : "127.0.0.1", 'port' : 1234}

        Returns:
            Tuple (host, port, token, error)
            if error is True, other fields are not present, for example:

            ("127.0.0.1", 1234, None, False)
            or
            (None, None, None, True)
        '''
        if 'host' not in params:
            self.__logger.warning("Host is not present")
            return (None, None, None, True)
        host = params['host']
        if not isinstance(host, str) or not host:
            # if host is not string or host is empty string
            self.__logger.warning("Incorrect host: `%s`", params['host'])
            return (None, None, None, True)

        if 'port' not in params:
            self.__logger.warning("Port is not present")
            return (None, None, None, True)
        try:
            port = int(params['port'])
        except ValueError:
            # if port can not be converted to integer
            self.__logger.warning("Incorrect port: `%s`", params['port'])
            return (None, None, None, True)

        token = params.get('token')
        return (host, port, token, False)

    def add(self, params):
        '''Adds new route between a application and SDL

        Args:
            params: dictionary of parameters of application, for example:

            {'host' : "127.0.0.1", 'port' : 1234}
        '''
        self.__logger.info("Add route %s", params)
        host, port, token, error = self.get_info(params)
        if not error:
            key = "%s:%i" % (host, port)
            if key not in self.__routes:
                self.__routes[key] = self.create(host, port)
                self.run(self.__routes[key], token)
            else:
                self.__logger.warning("Route %s already exists", key)

    def run(self, way, token=None):
        '''Runs route

        Args:
            way: routing.Route instance
            token: string of token
        '''
        if token:
            credentials = {'vin': self.__config.vin(), 'token': token}
            way.start(credentials)
        else:
            way.start()

    def create(self, host, port):
        '''Creates route

        Args:
            host : string of the host
            port : integer of the port number

        Returns:
            instance of routing.Route
        '''
        self.__logger.info("Create route %s:%i", host, port)
        return route.create(
            connection.create(host, port),
            connection.create(self.__config.sdl_host(),
                              self.__config.sdl_port()))

    def refresh(self):
        '''Removes routes which are not running'''
        self.__logger.info("Refresh routes")
        self.__logger.debug("Number of routes %i", len(self.__routes))
        remove = [key for key, way in self.__routes.items()
                  if not way.running()]
        for key in remove:
            self.__logger.info("Route %s is inactive", key)
            del self.__routes[key]

    def stop(self):
        '''Stops routes between all applications and SDL'''
        self.__logger.info("Stop all routes")
        self.__running = False
        self.__routes.clear()

    def loop(self):
        '''Runs loop of handling connections'''
        while self.running():
            if self.__config.timeout() < 30:
                asyncore.loop(timeout=self.__config.timeout())
            else:
                asyncore.loop()

    def running(self):
        '''Gets state of loop

        Returns:
            True if loop is running
        '''
        return self.__running
