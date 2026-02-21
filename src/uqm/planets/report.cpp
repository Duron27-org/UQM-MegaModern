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

#include "lander.h"
#include "scan.h"
#include "planets.h"
#include "../colors.h"
#include "../controls.h"
#include "../gamestr.h"
#include "../setup.h"
#include "../util.h"
#include "../sounds.h"
#include "../uqmdebug.h"
#include "options.h"
#include "libs/inplib.h"
#include "../nameref.h"
#include "../ifontres.h"
#include "../igfxres.h"

#include <ctype.h>
#include <string.h>
#include "../lua/luacomm.h"


#define COL_MULTIPLIER (isPC(optSuperPC) || IS_PAD ? 7 : 6)
#define NUM_CELL_COLS (UQM_MAP_WIDTH / COL_MULTIPLIER)
#define NUM_CELL_ROWS (SC2_MAP_HEIGHT / 6)
#define MAX_CELL_COLS 40 // Why is this is never used???

extern FRAME SpaceJunkFrame;

static void
ClearReportArea(COORD startx)
{
	uqm::COUNT x, y;
	GFXRECT r;
	STAMP s;

	if (optWhichFonts == uqm::EmulationMode::PC)
	{
		s.frame = SetAbsFrameIndex(SpaceJunkFrame, 21);
	}
	else
	{
		s.frame = SetAbsFrameIndex(SpaceJunkFrame, 18);
	}
	GetFrameRect(s.frame, &r);
	BatchGraphics();

	SetContextBackGroundColor(BLACK_COLOR);
	ClearDrawable();
	SetContextForeGroundColor(
		BUILD_COLOR(MAKE_RGB15(0x00, 0x07, 0x00), 0x57));

	s.origin.y = RES_SCALE(1);
	for (y = 0; y < NUM_CELL_ROWS; ++y)
	{
		s.origin.x = startx;
		for (x = 0; x < NUM_CELL_COLS; ++x)
		{
			if (optWhichFonts == uqm::EmulationMode::PC)
			{
				DrawStamp(&s);
			}
			else
			{
				DrawFilledStamp(&s);
			}

			s.origin.x += r.extent.width + RES_SCALE(1);
		}
		s.origin.y += r.extent.height + RES_SCALE(1);
	}

	UnbatchGraphics();
}

static void
MakeReport(SOUND ReadOutSounds, uqm::CHAR_T* pStr, uqm::COUNT StrLen)
{
	int end_page_len;
	uqm::CHAR_T end_page_buf[200] {};
	UniChar last_c = 0;
	uqm::COUNT row_cells;
	bool Sleepy;
	GFXRECT r, contextRect;
	TEXT t;
	Color fgcolor;
	COORD startx;

	uqm::SIZE total_lines = -1;
	uqm::SIZE curr_line = -1;
	uqm::COUNT first_line_length = 0;

	fmt::format_to_n(end_page_buf, sizeof(end_page_buf) - 1, "{}\n",
					 GAME_STRING(static_cast<int>(SCAN_STRING_BASE) + static_cast<int>(NUM_SCAN_TYPES)));
	end_page_len = utf8StringCount(end_page_buf);

	GetFrameRect(SetAbsFrameIndex(SpaceJunkFrame, 18), &r);
	GetContextClipRect(&contextRect);

	t.align = ALIGN_LEFT;
	t.CharCount = 1;
	t.pStr = pStr;
	Sleepy = true;

	FlushInput();

	t.baseline.y = r.extent.height + RES_SCALE(1);
	// Text vertical alignment
	row_cells = 0;
	fgcolor = BUILD_COLOR(MAKE_RGB15(0x00, 0x1F, 0x00), 0xFF);

	if (contextRect.extent.width < SCALED_MAP_WIDTH)
	{
		startx = RES_SCALE(1); // Special case if we're in space
	}
	else
	{ // In DOS version first cell is 3p away from the edge of the
		// context, and 2 in UQM
		startx = RES_SCALE(RES_DESCALE(r.extent.width) >> 1)
			   + (isPC(optSuperPC) ? RES_SCALE(1) : 0);
	}

	startx += SAFE_NUM_SCL(1);

	if (StrLen)
	{
		ClearReportArea(startx);
		SetContextForeGroundColor(fgcolor);

		if (is3DO(optSuperPC))
		{
			const uqm::CHAR_T* pCurrStr;
			uqm::COUNT length;

			pCurrStr = t.pStr;
			total_lines = 0;
			curr_line = 0;

			for (length = StrLen; length > 0; length--)
			{
				if (getCharFromString(&pCurrStr) == '\n')
				{
					total_lines++;
				}

				if (total_lines == 0)
				{
					first_line_length++;
				}
			}
		}
	}

	while (StrLen)
	{
		uqm::COUNT col_cells;
		const uqm::CHAR_T* pLastStr;
		const uqm::CHAR_T* pNextStr;
		uqm::COUNT lf_pos;

		pLastStr = t.pStr;

		// scan for LFs in the remaining string
		// trailing LF will be ignored
		for (lf_pos = StrLen, pNextStr = t.pStr;
			 lf_pos && getCharFromString(&pNextStr) != '\n';
			 --lf_pos)
			;

		col_cells = 0;
		// check if the remaining text fits on current screen
		if (row_cells == NUM_CELL_ROWS - 1
			&& (StrLen > NUM_CELL_COLS || lf_pos > 1))
		{
			col_cells = (NUM_CELL_COLS >> 1) - (end_page_len >> 1);
			t.pStr = end_page_buf;
			StrLen += end_page_len;

			// We're adding lines - compensate for it
			if (curr_line >= 0)
			{
				curr_line--;
			}
		}
		if (total_lines >= 0)
		{
			if (curr_line == 0)
			{
				col_cells = (NUM_CELL_COLS - first_line_length) >> 1;
			}

			if (curr_line == total_lines)
			{
				col_cells = ((NUM_CELL_COLS - (StrLen - 2)) >> 1) - 2;
			}
		}

		t.baseline.x = startx + (col_cells * (r.extent.width + RES_SCALE(1)));

		do
		{
			uqm::COUNT word_chars;
			const uqm::CHAR_T* pStr;
			UniChar c;

			pStr = t.pStr;
			pNextStr = t.pStr;
			while (UniChar_isGraph(getCharFromString(&pNextStr)))
			{
				pStr = pNextStr;
			}

			word_chars = (uqm::COUNT)utf8StringCountN(t.pStr, pStr);
			if ((col_cells += word_chars) <= NUM_CELL_COLS)
			{
				TimeCount TimeOut;

				if (StrLen -= word_chars)
				{
					--StrLen;
				}
				TimeOut = GetTimeCounter();
				while (word_chars--)
				{
					pNextStr = t.pStr;
					c = getCharFromString(&pNextStr);

					if (GLOBAL(CurrentActivity) & CHECK_ABORT)
					{
						return;
					}
					if (!Sleepy)
					{
						font_DrawText(&t);
					}
					else
					{
						uqm::BYTE scale = 0;
						font_DrawText(&t);

						if (CurrentInputState.menu[KEY_MENU_RIGHT])
						{
							scale = 2;
						}

						PlaySound(ReadOutSounds, NotPositional(), nullptr,
								  GAME_SOUND_PRIORITY);

						switch (c)
						{
							case ',':
								TimeOut += GameTicksPerSecond / (4 << scale);
								break;
							case '.':
								TimeOut += GameTicksPerSecond / (2 << scale);
								break;
							case '!':
								if (last_c != '!' && last_c != ' ')
								{
									TimeOut += GameTicksPerSecond / (2 << scale);
								}
								else
								{
									TimeOut += GameTicksPerSecond / (20 << scale);
								}
								break;
							case '?':
								if (last_c != '?' && last_c != ' ')
								{
									TimeOut += GameTicksPerSecond / (2 << scale);
								}
								else
								{
									TimeOut += GameTicksPerSecond / (20 << scale);
								}
								break;
							default:
								TimeOut += GameTicksPerSecond / (20 << scale);
								break;
						}

						last_c = c;

						if (word_chars == 0)
						{
							TimeOut += GameTicksPerSecond / (20 << scale);
						}

						if (WaitForActButtonUntil(true, TimeOut, false))
						{
							Sleepy = false;
							// We draw the whole thing at once after this
							BatchGraphics();
						}
					}
					t.pStr = pNextStr;
					t.baseline.x += r.extent.width + RES_SCALE(1);
					// Text spacing
				}

				++col_cells;
				last_c = getCharFromString(&t.pStr);
				t.baseline.x += r.extent.width + RES_SCALE(1);
				// Space spacing

				if (curr_line >= 0 && last_c == '\n')
				{
					curr_line++;
				}
			}
		} while (col_cells <= NUM_CELL_COLS && last_c != '\n' && StrLen);

		t.baseline.y += r.extent.height + RES_SCALE(1);
		// Text vertical spacing
		if (++row_cells == NUM_CELL_ROWS || StrLen == 0)
		{
			t.pStr = pLastStr;
			if (!Sleepy)
			{
				UnbatchGraphics();
			}

			if (!WaitForActButton(true, WAIT_INFINITE, false))
			{
				break;
			}

			t.baseline.y = r.extent.height + RES_SCALE(1);
			// Text vertical alignment
			row_cells = 0;
			if (StrLen)
			{
				if (!Sleepy)
				{
					BatchGraphics();
				}
				ClearReportArea(startx);
				SetContextForeGroundColor(fgcolor);
			}
		}
	}
}

void DoDiscoveryReport(SOUND ReadOutSounds)
{
	GFXCONTEXT OldContext;
	GFXCONTEXT context;
	bool ownContext;
	STAMP saveStamp;

#ifdef DEBUG
	if (disableInteractivity)
	{
		return;
	}
#endif

	context = GetScanContext(&ownContext);
	OldContext = SetContext(context);
	saveStamp = SaveContextFrame(nullptr);
	{
		FONT OldFont;
		FRAME OldFontEffect;

		OldFont = SetContextFont(
			pSolarSysState->SysInfo.PlanetInfo.LanderFont);
		if (optWhichFonts == uqm::EmulationMode::PC)
		{
			OldFontEffect = SetContextFontEffect(
				pSolarSysState->SysInfo.PlanetInfo.LanderFontEff);
		}
		else
		{
			OldFontEffect = SetContextFontEffect(nullptr);
		}

		luaUqm_comm_init(nullptr, NULL_RESOURCE);
		bool allocated = false;
		char* StrPtr = (uqm::CHAR_T*)GetStringAddress(pSolarSysState->SysInfo.PlanetInfo.DiscoveryString);
		if (luaUqm_comm_stringNeedsInterpolate(StrPtr))
		{
			allocated = true;
			StrPtr = luaUqm_comm_stringInterpolate(StrPtr);
		}
		MakeReport(ReadOutSounds, StrPtr, (uqm::COUNT)strlen(StrPtr));

		luaUqm_comm_uninit();
		if (allocated)
		{
			HFree(StrPtr);
		}

		SetContextFontEffect(OldFontEffect);
		SetContextFont(OldFont);
	}
	// Restore previous screen
	DrawStamp(&saveStamp);
	SetContext(OldContext);
	// TODO: Make GFXCONTEXT ref-counted
	if (ownContext)
	{
		DestroyScanContext();
	}

	DestroyDrawable(ReleaseDrawable(saveStamp.frame));

	WaitForNoInput(WAIT_INFINITE, true);
}