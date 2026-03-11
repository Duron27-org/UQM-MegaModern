/*
 * Copyright (C) 2003  Serge van den Boom
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 * Nota bene: later versions of the GNU General Public License do not apply
 * to this program.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef LIBS_UIO_UIOUTILS_H_
#define LIBS_UIO_UIOUTILS_H_

#include <time.h>

#include <cstdint>
#include "uioport.h"

char* strcata(const char* first, const char* second);
void* insertArray(const void* array, size_t oldNumElements, int insertPos,
				  const void* element, size_t elementSize);
void** insertArrayPointer(const void** array, size_t oldNumElements,
						  int insertPos, const void* element);
void* excludeArray(const void* array, size_t oldNumElements, int startPos,
				   int numExclude, size_t elementSize);
void** excludeArrayPointer(const void** array, size_t oldNumElements,
						   int startPos, int numExclude);
time_t dosToUnixTime(uint16_t date, uint16_t tm);
char* dosToUnixPath(const char* path);

/* Sometimes you just have to remove a 'const'.
 * (for instance, when implementing a function like strchr)
 */
//static inline void *
//unconst(const void *arg) {
//	union {
//		void *c;
//		const void *cc;
//	} u;
//	u.cc = arg;
//	return u.c;
//}
template <typename T>
inline T* unconst(const T* arg) { return const_cast<T*>(arg); }


// byte1 is the lowest byte, byte4 the highest
static inline uint32_t
makeUInt32(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4)
{
	return byte1 | (byte2 << 8) | (byte3 << 16) | (byte4 << 24);
}

static inline uint16_t
makeUInt16(uint8_t byte1, uint8_t byte2)
{
	return byte1 | (byte2 << 8);
}

static inline int32_t
makeSInt32(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4)
{
	return byte1 | (byte2 << 8) | (byte3 << 16) | (byte4 << 24);
}

static inline int16_t
makeSInt16(uint8_t byte1, uint8_t byte2)
{
	return byte1 | (byte2 << 8);
}

static inline bool
isBitSet(uint32_t bitField, int bit)
{
	return ((bitField >> bit) & 1) == 1;
}

static inline int
mins(int i1, int i2)
{
	return i1 <= i2 ? i1 : i2;
}

static inline unsigned int
minu(unsigned int i1, unsigned int i2)
{
	return i1 <= i2 ? i1 : i2;
}


#endif /* LIBS_UIO_UIOUTILS_H_ */
