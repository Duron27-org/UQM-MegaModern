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

/*
 * LZHUF.C English version 1.0
 * Based on Japanese version 29-NOV-1988
 * LZSS coded by Haruhiko OKUMURA
 * Adaptive Huffman Coding coded by Haruyasu YOSHIZAKI
 * Edited and translated to English by Kenji RIKITAKE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lzh.h"
#include "libs/reslib.h"

PLZHCODE_DESC _lpCurCodeDesc;
STREAM_TYPE _StreamType;
uint8_t* _Stream;
uint16_t _workbuf;
uint8_t _workbuflen;

/* get one bit */
static int16_t
GetBit(void)
{
	int16_t i;

	while (_workbuflen <= 8)
	{
		if ((i = InChar()) < 0)
		{
			i = 0;
		}
		_workbuf |= i << (8 - _workbuflen);
		_workbuflen += 8;
	}
	i = (_workbuf & 0xFFFF) >> (16 - 1);
	_workbuf = (_workbuf << 1) & 0xFFFF;
	_workbuflen--;

	return (i);
}

static uint16_t
GetBits(uint8_t num_bits)
{
	int16_t i;

	while (_workbuflen <= 8)
	{
		if ((i = InChar()) < 0)
		{
			i = 0;
		}
		_workbuf |= i << (8 - _workbuflen);
		_workbuflen += 8;
	}
	i = (_workbuf & 0xFFFF) >> (16 - num_bits);
	_workbuf = (_workbuf << num_bits) & 0xFFFF;
	_workbuflen -= num_bits;

	return (i);
}

/* initialize freq tree */

void StartHuff(void)
{
	uint16_t i, j;

	for (i = 0; i < HUF_NumChars; i++)
	{
		_lpCurCodeDesc->freq[i] = 1;
		_lpCurCodeDesc->son[i] = i + HUF_TableSize;
		_lpCurCodeDesc->prnt[i + HUF_TableSize] = i;
	}
	i = 0;
	j = HUF_NumChars;
	while (j <= HUF_Root)
	{
		_lpCurCodeDesc->freq[j] = _lpCurCodeDesc->freq[i] + _lpCurCodeDesc->freq[i + 1];
		_lpCurCodeDesc->son[j] = i;
		_lpCurCodeDesc->prnt[i] = _lpCurCodeDesc->prnt[i + 1] = j;
		i += 2;
		j++;
	}
	_lpCurCodeDesc->freq[HUF_TableSize] = 0xffff;
	_lpCurCodeDesc->prnt[HUF_Root] = 0;
}

DECODE_REF
copen(void* InStream, STREAM_TYPE SType, STREAM_MODE SMode)
{
	uint32_t StreamLength;

	_StreamType = SType;
	_Stream = (uint8_t*)InStream;
	if (SMode == STREAM_WRITE) /* writing */
	{
		OutChar(0); /* skip future StreamLength */
		OutChar(0);
		OutChar(0);
		OutChar(0);

		StreamLength = 0;
	}
	else /* reading */
	{
		uint8_t lobyte, hibyte;
		uint16_t loword, hiword;

		lobyte = (uint8_t)InChar();
		hibyte = (uint8_t)InChar();
		loword = MAKE_WORD(lobyte, hibyte);
		lobyte = (uint8_t)InChar();
		hibyte = (uint8_t)InChar();
		hiword = MAKE_WORD(lobyte, hibyte);

		StreamLength = MAKE_DWORD(loword, hiword);
	}

	if (StreamLength == 0xFFFFFFFF
		|| (_lpCurCodeDesc = (PLZHCODE_DESC)AllocCodeDesc()) == nullptr)
	{
		FreeCodeDesc(_lpCurCodeDesc);
		_lpCurCodeDesc = nullptr;
	}
	else
	{
		_lpCurCodeDesc->Stream = _Stream;
		_lpCurCodeDesc->StreamType = _StreamType;
		_lpCurCodeDesc->StreamMode = SMode;
		_lpCurCodeDesc->StreamLength = StreamLength;
		_lpCurCodeDesc->buf_index = LZSS_BufferSize - LZSS_LookAheadBufferSize;
		memset(&_lpCurCodeDesc->text_buf[0], ' ', LZSS_BufferSize - LZSS_LookAheadBufferSize);

		StartHuff();
	}

	return ((DECODE_REF)_lpCurCodeDesc);
}

uint32_t
cclose(PLZHCODE_DESC lpCodeDesc)
{
	_lpCurCodeDesc = lpCodeDesc;
	if (_lpCurCodeDesc)
	{
		uint32_t StreamIndex;

		if (_lpCurCodeDesc->CleanupFunc)
		{
			(*_lpCurCodeDesc->CleanupFunc)();
		}

		StreamIndex = lpCodeDesc->StreamIndex;
		FreeCodeDesc(lpCodeDesc);
		_lpCurCodeDesc = nullptr;

		return (StreamIndex);
	}

	return (0);
}

void cfilelength(PLZHCODE_DESC lpCodeDesc, uint32_t* pfilelen)
{
	if (lpCodeDesc == 0)
	{
		*pfilelen = 0;
	}
	else
	{
		*pfilelen = lpCodeDesc->StreamLength;
	}
}

/* decoder table */
static const uint8_t d_code[256] =
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x07,
		0x07,
		0x07,
		0x07,
		0x07,
		0x07,
		0x07,
		0x07,
		0x08,
		0x08,
		0x08,
		0x08,
		0x08,
		0x08,
		0x08,
		0x08,
		0x09,
		0x09,
		0x09,
		0x09,
		0x09,
		0x09,
		0x09,
		0x09,
		0x0A,
		0x0A,
		0x0A,
		0x0A,
		0x0A,
		0x0A,
		0x0A,
		0x0A,
		0x0B,
		0x0B,
		0x0B,
		0x0B,
		0x0B,
		0x0B,
		0x0B,
		0x0B,
		0x0C,
		0x0C,
		0x0C,
		0x0C,
		0x0D,
		0x0D,
		0x0D,
		0x0D,
		0x0E,
		0x0E,
		0x0E,
		0x0E,
		0x0F,
		0x0F,
		0x0F,
		0x0F,
		0x10,
		0x10,
		0x10,
		0x10,
		0x11,
		0x11,
		0x11,
		0x11,
		0x12,
		0x12,
		0x12,
		0x12,
		0x13,
		0x13,
		0x13,
		0x13,
		0x14,
		0x14,
		0x14,
		0x14,
		0x15,
		0x15,
		0x15,
		0x15,
		0x16,
		0x16,
		0x16,
		0x16,
		0x17,
		0x17,
		0x17,
		0x17,
		0x18,
		0x18,
		0x19,
		0x19,
		0x1A,
		0x1A,
		0x1B,
		0x1B,
		0x1C,
		0x1C,
		0x1D,
		0x1D,
		0x1E,
		0x1E,
		0x1F,
		0x1F,
		0x20,
		0x20,
		0x21,
		0x21,
		0x22,
		0x22,
		0x23,
		0x23,
		0x24,
		0x24,
		0x25,
		0x25,
		0x26,
		0x26,
		0x27,
		0x27,
		0x28,
		0x28,
		0x29,
		0x29,
		0x2A,
		0x2A,
		0x2B,
		0x2B,
		0x2C,
		0x2C,
		0x2D,
		0x2D,
		0x2E,
		0x2E,
		0x2F,
		0x2F,
		0x30,
		0x31,
		0x32,
		0x33,
		0x34,
		0x35,
		0x36,
		0x37,
		0x38,
		0x39,
		0x3A,
		0x3B,
		0x3C,
		0x3D,
		0x3E,
		0x3F,
};
static const uint8_t d_len[256] =
	{
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x01,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x02,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x03,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x05,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
		0x06,
};

/* decode upper 6 bits from given table */
#define DecodePosition(p)                           \
	{                                               \
		while (_workbuflen <= 8)                    \
		{                                           \
			*(p) = InChar();                        \
			_workbuf |= *(p) << (8 - _workbuflen);  \
			_workbuflen += 8;                       \
		}                                           \
		*(p) = highByte(_workbuf);                  \
		_workbuf = (_workbuf << 8) & 0xFFFF;        \
		_workbuflen -= 8;                           \
                                                    \
		/* input lower 6 bits directly */           \
		j = d_len[*(p)];                            \
		*(p) = ((uint16_t)d_code[*(p)] << 6)        \
			 | (((*(p) << j) | GetBits(j)) & 0x3f); \
	}

/* start searching tree from the root to leaves.
	 * choose node #(son[]) if input bit == 0
	 * else choose #(son[]+1) (input bit == 1)
	 */
#define DecodeChar(c)                                 \
	{                                                 \
		for (*(c) = lpCodeDesc->son[HUF_Root];        \
			 *(c) < HUF_TableSize;                    \
			 *(c) = lpCodeDesc->son[*(c) + GetBit()]) \
			;                                         \
		_update(*(c));                                \
		*(c) -= HUF_TableSize;                        \
	}

uint16_t
cread(void* buf, uint16_t size, uint16_t count, PLZHCODE_DESC lpCodeDesc)
{
	uint16_t r, j, i;
	uint8_t* lpStr;

	if ((_lpCurCodeDesc = lpCodeDesc) == 0)
	{
		return (0);
	}

	size *= count;
	if (lpCodeDesc->StreamIndex + size > lpCodeDesc->StreamLength)
	{
		size /= count;
		count = (uint16_t)((lpCodeDesc->StreamLength
							- lpCodeDesc->StreamIndex)
						   / size);

		size *= count;
	}

	if (size == 0)
	{
		return (0);
	}

	lpStr = (uint8_t*)buf;
	_StreamType = lpCodeDesc->StreamType;

	_Stream = (uint8_t*)lpCodeDesc->Stream;
	_workbuf = lpCodeDesc->workbuf;
	_workbuflen = lpCodeDesc->workbuflen;

	lpCodeDesc->StreamIndex += size;
	r = lpCodeDesc->buf_index;
	j = lpCodeDesc->bytes_left;
	if (j)
	{
		lpCodeDesc->bytes_left = 0;
		i = lpCodeDesc->restart_index;

		goto ReenterRun;
	}

	do
	{
		uint16_t c;

		DecodeChar(&c);

		if (c < 256)
		{
			size--;

			*lpStr++ = lpCodeDesc->text_buf[r++ & (LZSS_BufferSize - 1)] = (uint8_t)c;
		}
		else
		{
			uint16_t copy_size;

			//i is a uint16_t;
			DecodePosition(&i);
			i = r - i - 1;
			j = c - 255 + LZSS_Threshold;
ReenterRun:
			if (j > size)
			{
				lpCodeDesc->bytes_left = j - size;
				lpCodeDesc->restart_index = i + size;
				j = size;
			}

			size -= j;
			do
			{
				uint16_t loc_size;

				i &= (LZSS_BufferSize - 1);
				r &= (LZSS_BufferSize - 1);
				if ((i < r && i + j > r) || (i > r && i + j > r + LZSS_BufferSize))
				{
					copy_size = (r - i) & (LZSS_BufferSize - 1);
				}
				else if ((copy_size = j) > LZSS_BufferSize)
				{
					copy_size = LZSS_BufferSize;
				}

				loc_size = copy_size;
				if (i + loc_size > LZSS_BufferSize)
				{
					uint16_t k;

					k = LZSS_BufferSize - i;
					memcpy(lpStr, &lpCodeDesc->text_buf[i], k);
					lpStr += k;
					loc_size -= k;
					i = 0;
				}

				memcpy(lpStr, &lpCodeDesc->text_buf[i], loc_size);
				lpStr += loc_size;
				i += loc_size;

				lpStr -= copy_size;

				loc_size = copy_size;
				if (r + loc_size > LZSS_BufferSize)
				{
					uint16_t k;

					k = LZSS_BufferSize - r;
					memcpy(&lpCodeDesc->text_buf[r], lpStr, k);
					lpStr += k;
					loc_size -= k;
					r = 0;
				}

				memcpy(&lpCodeDesc->text_buf[r], lpStr, loc_size);
				lpStr += loc_size;
				r += loc_size;
			} while (j -= copy_size);
		}
	} while (size);

	lpCodeDesc->buf_index = r;
	lpCodeDesc->Stream = _Stream;
	lpCodeDesc->workbuf = _workbuf;
	lpCodeDesc->workbuflen = _workbuflen;

	return (count);
}
