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

__push_errno_defs
#undef __CUSTOM_ERRNO_DEFS
#define __CUSTOM_ERRNO_DEFS __pop_errno_defs __CUSTOM_ERRNO_DEFS	\
	ERESOLVE,

__push_errno_strs
#undef __CUSTOM_ERRNO_STRS
#define __CUSTOM_ERRNO_STRS __pop_errno_strs __CUSTOM_ERRNO_STRS	\
	"Failed to resolve provided hostname or IP",
