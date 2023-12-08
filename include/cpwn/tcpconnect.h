/*
 * A library that facilitates exploit development in C
 * Copyright (C) 2023  Sabrina Andersen (NukingDragons)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _TCPCONNECT_H_
#define _TCPCONNECT_H_

#include <stdint.h>
#include <error.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int tcpconnect(char *hostname, char *port)
{
	set_errno(ESUCCESS);

	int sock = -1;

	if (hostname && port)
	{
		int err = 0;
		struct addrinfo *info = 0;

		// Enforce tcp
		struct addrinfo hints;
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;

		// Attempt to resolve the address
		if (!(err = getaddrinfo(hostname, port, &hints, &info)))
		{
			// Loop through the addresses attempting to connect to each one until a successful connection occurs
			for (struct addrinfo *i = info; i != 0; i = i->ai_next)
			{
				sock = socket(i->ai_family, i->ai_socktype, i->ai_protocol);

				if (sock <= -1)
					continue;

				if (!(err = connect(sock, i->ai_addr, i->ai_addrlen)))
					break;
			}

			freeaddrinfo(info);
		}
		else
			set_errno(ERESOLVE);

		// An error occured, free the socket
		if ((errno || err) && sock)
		{
			close(sock);
			sock = -1;
		}
	}
	else
		set_errno(EINVAL);

	return sock;
}

#endif
