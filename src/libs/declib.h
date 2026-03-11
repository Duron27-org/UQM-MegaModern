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

#ifndef LIBS_DECLIB_H_
#define LIBS_DECLIB_H_

#include "libs/compiler.h"

#if 0 //defined(__cplusplus)
extern "C" {
#endif

typedef struct _LZHCODE_DESC* DECODE_REF;

enum
{
	FILE_STREAM = 0,
	MEMORY_STREAM
};
typedef uint8_t STREAM_TYPE;

enum
{
	STREAM_READ = 0,
	STREAM_WRITE
};
typedef uint8_t STREAM_MODE;

extern DECODE_REF copen(void* InStream, STREAM_TYPE SType,
						STREAM_MODE SMode);
extern uint32_t cclose(DECODE_REF DecodeRef);
extern void cfilelength(DECODE_REF DecodeRef, uint32_t* pfilelen);
extern uint16_t cread(void* pStr, uint16_t size, uint16_t count,
					  DECODE_REF DecodeRef);
extern uint16_t cwrite(const void* pStr, uint16_t size, uint16_t count,
					   DECODE_REF DecodeRef);

#if 0 //defined(__cplusplus)
}
#endif

#endif /* LIBS_DECLIB_H_ */
