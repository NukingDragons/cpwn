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

#ifndef _AMD64_SROP_H_
#define _AMD64_SROP_H_

#include <stdint.h>

#pragma pack(push, 1)

struct amd64_srop_frame
{
	uint64_t mask;
	uint64_t _reserved;
	uint64_t fpstate;
	uint64_t cr2;
	uint64_t oldmask;
	uint64_t trapno;
	uint64_t err;
	uint64_t cs:2;
	uint64_t gs:2;
	uint64_t fs:2;
	uint64_t _padding:2;
	uint64_t eflags;
	uint64_t rip;
	uint64_t rsp;
	uint64_t rcx;
	uint64_t rax;
	uint64_t rdx;
	uint64_t rbx;
	uint64_t rbp;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	uint64_t ss_size;
	uint64_t ss_flags;
	uint64_t ss_sp;
	uint64_t uc_link;
	uint64_t uc_flags;
};

#pragma pack(pop)

#endif
