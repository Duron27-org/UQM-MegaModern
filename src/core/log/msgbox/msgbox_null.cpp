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

#include "msgbox.h"
#if defined(ANDROID) || defined(__ANDROID__)
#include <android/log.h>
#endif

namespace uqm
{

void displayMessageBox(uqgsl::czstring utf8Title, uqgsl::czstring utf8Message, MessageBoxType type);
{
	const bool isError {type == MessageBoxType::Error};
	// We do not know how to display a box. Perhaps it's done with a
	// hefty dose of pixie dust, or perhaps with a hammer and nails.
	// So just inform the user of our predicament
	fmt::print(streamOut, "Do not know how to display {} box. Message follows:\n----------------------\n{}\n{}", isError ? "an error" : "a message", utf8Title, utf8Message);
#if defined(ANDROID) || defined(__ANDROID__)
	__android_log_print(isError ? ANDROID_LOG_FATAL : ANDROID_LOG_INFO, "Ur-Quan Masters MegaMod", "{}: {}", title, msg);
#endif

	// Suppress the compiler warnings in any case.
	uqstl::ignore = title;
	uqstl::ignore = msg;
}

} // namespace uqm