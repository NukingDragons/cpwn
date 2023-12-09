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

#ifndef _RECVUNTIL_H_
#define _RECVUNTIL_H_

#include <stdint.h>
#include <stdlib.h>
#include <error.h>

#include <unistd.h>

#ifndef RECVUNTIL_BUFLEN
#define RECVUNTIL_BUFLEN 0x4000
#endif

#ifndef RECVUNTIL_STEPSIZE
#define RECVUNTIL_STEPSIZE 0x1000
#endif

uint8_t recvuntil(int sock, void *data, uint64_t data_len)
{
	uint8_t found = 0;

	if (sock > -1 && data && data_len)
	{
		uint64_t response_index = 0;
		uint64_t response_size = RECVUNTIL_BUFLEN;
		uint8_t *response = malloc(response_size);

		if (response)
		{
			memset(response, 0, response_size);

			while(!errno)
			{
				// Only read 1 character at a time, even though it's not super efficient
				// The goal is to only read until the data block. Then, future attempts
				// to read from the socket will read data IMMIDIATELY following the data block
				uint64_t read_len = read(sock, &response[response_index], 1);
				if (read_len <= 0)
					break;
				response_index += read_len;

				// Scan the response buffer for the data
				for (uint64_t i = 0; i < response_index; i++)
				{
					// Only scan the full data_len
					if (data_len > (response_index + i))
						break;

					if (!memcmp(&response[i], data, data_len))
						found = 1;
				}

				if (found)
					break;

				if (response_index + RECVUNTIL_STEPSIZE > response_size)
				{
					response_size += RECVUNTIL_BUFLEN;
					response = realloc(response, response_size);
					memset(&response[response_size - RECVUNTIL_BUFLEN], 0, RECVUNTIL_BUFLEN);
				}
			}

			free(response);
		}
	}
	else
		set_errno(EINVAL);

	return found;
}

#endif
