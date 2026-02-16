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
#pragma once
#include "core/stl/stl.h"
#include "options/options.h"
#include "core/log/logger.h"

namespace uqm
{

class UQMGame
{
public:
	UQMGame();

	[[nodiscard]] int setup(uqstl::span<uqgsl::czstring const> args);
	[[nodiscard]] int run();
	void teardown();

private:
	OptionsStruct m_options {};
	Logger m_logger {};
};

} // namespace uqm