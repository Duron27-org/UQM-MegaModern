//Copyright Paul Reiche, Fred Ford. 1992-2002

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef LIBS_COMPILER_H_
#define LIBS_COMPILER_H_

#include "types.h"

#if 0 //defined(__cplusplus)
extern "C" {
#endif

namespace uqm
{
typedef uint8             BYTE;
typedef uint8             UBYTE;
typedef sint8             SBYTE;
typedef uint16            UWORD;
typedef sint16            SWORD;
typedef uint32            DWORD;
typedef sint32           SDWORD;
typedef uint64            QWORD;
typedef sint64           SQWORD;

typedef UWORD             COUNT;
typedef SWORD             SIZE;

typedef char            CHAR_T;
}

typedef void     (*PVOIDFUNC) (void);
typedef bool  (*PBOOLFUNC) (void);
typedef uqm::BYTE     (*PBYTEFUNC) (void);
typedef uqm::UWORD    (*PUWORDFUNC) (void);
typedef uqm::SWORD    (*PSWORDFUNC) (void);
typedef uqm::DWORD    (*PDWORDFUNC) (void);

#define MAKE_BYTE(lo, hi)   ((uqm::BYTE) (((uqm::BYTE) (hi) << (uqm::BYTE) 4) | (uqm::BYTE) (lo)))
#define LONIBBLE(x)  ((uqm::BYTE) ((uqm::BYTE) (x) & (uqm::BYTE) 0x0F))
#define HINIBBLE(x)  ((uqm::BYTE) ((uqm::BYTE) (x) >> (uqm::BYTE) 4))
#define MAKE_WORD(lo, hi)   ((uqm::UWORD) ((uqm::BYTE) (hi) << 8) | (uqm::BYTE) (lo))
//#define lowByte(x)    ((uqm::BYTE) ((uqm::UWORD) (x)))
template <typename T, std::enable_if_t<std::is_integral_v<T>,bool> = true>
constexpr inline auto lowByte(T x) -> uqm::BYTE
{
	return static_cast<uqm::BYTE>(x & T{0xFF});
}
//#define highByte(x)    ((uqm::BYTE) ((uqm::UWORD) (x) >> 8))
template <typename T>
constexpr inline auto highByte(T x) -> uqm::BYTE
{
	if constexpr (sizeof(T)==1)
	{
		return x;
	}
	else
	{
		return static_cast<uqm::BYTE>(x >> 8);
	}
}
#define MAKE_DWORD(lo, hi)  (((uqm::DWORD) (hi) << 16) | (uqm::UWORD) (lo))
#if !defined(LOWORD)
	#define LOWORD(x)    ((uqm::UWORD) ((uqm::DWORD) (x)))
#endif
#if !defined(HIWORD)
	#define HIWORD(x)    ((uqm::UWORD) ((uqm::DWORD) (x) >> 16))
#endif


// To be moved to port.h:
// _ALIGNED_ANY specifies an alignment suitable for any type
// _ALIGNED_ON specifies a caller-supplied alignment (should be a power of 2)
#if defined(__GNUC__)
#	define _PACKED __attribute__((packed))
#	define _ALIGNED_ANY __attribute__((aligned))
#	define _ALIGNED_ON(bytes) __attribute__((aligned(bytes)))
#elif defined(_MSC_VER)
#	define _ALIGNED_ANY
//#	define _ALIGNED_ON(bytes) __declspec(align(bytes))
			// __declspec(align(bytes)) expects a constant. 'sizeof (type)'
			// will not do. This is something that needs some attention,
			// once we find someone with a 64 bits Windows machine.
			// Leaving it alone for now.
#	define _PACKED
#	define _ALIGNED_ON(bytes)
#elif defined(__ARMCC__)
#	define _PACKED __attribute__((packed))
#	define _ALIGNED_ANY __attribute__((aligned))
#	define _ALIGNED_ON(bytes) __attribute__((aligned(bytes)))
#elif defined(__WINSCW__)
#	define _PACKED
#	define _ALIGNED_ANY
#	define _ALIGNED_ON(bytes)
#endif

#if 0 //defined(__cplusplus)
}
#endif

#endif /* LIBS_COMPILER_H_ */

