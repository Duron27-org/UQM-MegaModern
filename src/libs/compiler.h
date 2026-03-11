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

#include <cstdint>
#include <type_traits>

typedef void (*PVOIDFUNC)(void);
typedef bool (*PBOOLFUNC)(void);
typedef uint8_t (*PBYTEFUNC)(void);
typedef uint16_t (*PUWORDFUNC)(void);
typedef int16_t (*PSWORDFUNC)(void);
typedef uint32_t (*PDWORDFUNC)(void);

#define MAKE_BYTE(lo, hi) ((uint8_t)(((uint8_t)(hi) << (uint8_t)4) | (uint8_t)(lo)))
#define LONIBBLE(x) ((uint8_t)((uint8_t)(x) & (uint8_t)0x0F))
#define HINIBBLE(x) ((uint8_t)((uint8_t)(x) >> (uint8_t)4))
#define MAKE_WORD(lo, hi) ((uint16_t)((uint8_t)(hi) << 8) | (uint8_t)(lo))
template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
constexpr inline auto lowByte(T x) -> uint8_t
{
	return static_cast<uint8_t>(x & T {0xFF});
}
template <typename T>
constexpr inline auto highByte(T x) -> uint8_t
{
	if constexpr (sizeof(T) == 1)
	{
		return x;
	}
	else
	{
		return static_cast<uint8_t>(x >> 8);
	}
}
#define MAKE_DWORD(lo, hi) (((uint32_t)(hi) << 16) | (uint16_t)(lo))
#if !defined(LOWORD)
#define LOWORD(x) ((uint16_t)((uint32_t)(x)))
#endif
#if !defined(HIWORD)
#define HIWORD(x) ((uint16_t)((uint32_t)(x) >> 16))
#endif


// To be moved to port.h:
// _ALIGNED_ANY specifies an alignment suitable for any type
// _ALIGNED_ON specifies a caller-supplied alignment (should be a power of 2)
#if defined(__GNUC__)
#define _PACKED __attribute__((packed))
#define _ALIGNED_ANY __attribute__((aligned))
#define _ALIGNED_ON(bytes) __attribute__((aligned(bytes)))
#elif defined(_MSC_VER)
#define _ALIGNED_ANY
//#	define _ALIGNED_ON(bytes) __declspec(align(bytes))
// __declspec(align(bytes)) expects a constant. 'sizeof (type)'
// will not do. This is something that needs some attention,
// once we find someone with a 64 bits Windows machine.
// Leaving it alone for now.
#define _PACKED
#define _ALIGNED_ON(bytes)
#elif defined(__ARMCC__)
#define _PACKED __attribute__((packed))
#define _ALIGNED_ANY __attribute__((aligned))
#define _ALIGNED_ON(bytes) __attribute__((aligned(bytes)))
#elif defined(__WINSCW__)
#define _PACKED
#define _ALIGNED_ANY
#define _ALIGNED_ON(bytes)
#endif


#endif /* LIBS_COMPILER_H_ */
