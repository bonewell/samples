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


def create(app_conn, sdl_conn):
    '''Creates new route

    Args:
        app_conn: core.Connection instance
        sdl_conn: routing.Connection instance
    '''
    return Route(app_conn, sdl_conn)


class Route(object):
    '''Represents a route between application and SDL'''
    __logger = logging.getLogger('core')

    def __init__(self, app_conn, sdl_conn):
        '''Constructor

        Args:
            app_conn: routing.Connection instance
            sdl_conn: routing.Connection instance
        '''
        self.__app_conn = app_conn
        self.__sdl_conn = sdl_conn
        self.__app_conn.link(self.__sdl_conn)
        self.__sdl_conn.link(self.__app_conn)

    def __del__(self):
        self.stop()
        del self.__app_conn
        del self.__sdl_conn

    def __eq__(self, other):
        # pylint: disable=protected-access
        return self.__app_conn == other.__app_conn and self.__sdl_conn == other.__sdl_conn

    def __str__(self):
        return "%s <=> %s" % (self.__app_conn, self.__sdl_conn)

    def start(self, credentials=None):
        '''Starts a route establishing'''
        self.__logger.info('Start route %s', self)
        self.__app_conn.open(credentials)
        self.__sdl_conn.open()

    def stop(self):
        '''Stops route'''
        self.__logger.info('Stop route %s', self)
        self.__app_conn.close()
        self.__sdl_conn.close()

    def running(self):
        '''Gets state of route

        Returns:
            True if both connections were established successfully
        '''
        return self.__app_conn.connected and self.__sdl_conn.connected
