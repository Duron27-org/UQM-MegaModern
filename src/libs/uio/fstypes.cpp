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

#include <errno.h>
#include <stdio.h>

#include "iointrn.h"
#include "uioport.h"
#include "fstypes.h"
#include "mem.h"
#include "defaultfs.h"
#ifdef uio_MEM_DEBUG
#include "memdebug.h"
#endif

#include <fmt/format.h>
#include "core/platform/platform.h"


static uio_bool uio_validFileSystemHandler(uio_FileSystemHandler* handler);
static uio_FileSystemInfo* uio_FileSystemInfo_new(uio_FileSystemID id,
												  uio_FileSystemHandler* handler, char* name);
static uio_FileSystemInfo** uio_getFileSystemInfoPtr(uio_FileSystemID id);

static inline uio_FileSystemInfo* uio_FileSystemInfo_alloc(void);

static inline void uio_FileSystemInfo_free(
	uio_FileSystemInfo* fileSystemInfo);


uio_FileSystemInfo* uio_fileSystems = nullptr;
// list sorted by id


void uio_registerDefaultFileSystems(void)
{
	int i;
	int num;
	uio_FileSystemID registerResult;

	num = uio_numDefaultFileSystems();
	for (i = 0; i < num; i++)
	{
		registerResult = uio_registerFileSystem(
			defaultFileSystems[i].id,
			defaultFileSystems[i].name,
			defaultFileSystems[i].handler);
		switch (registerResult)
		{
			case 0:
				fmt::print(stderr, "Warning: Default file system '{}' is "
								   "already registered.\n",
						   defaultFileSystems[i].name);
				break;
			case -1:
				fmt::print(stderr, "Error: Could not register '{}' file \n"
								   "system: {}\n",
						   defaultFileSystems[i].name,
						   uqm::strerror(errno));
				break;
			default:
				assert(registerResult == defaultFileSystems[i].id);
				break;
		}
	}
}

void uio_unRegisterDefaultFileSystems(void)
{
	int i;
	int num;

	num = uio_numDefaultFileSystems();
	for (i = 0; i < num; i++)
	{
		if (uio_unRegisterFileSystem(defaultFileSystems[i].id) == -1)
		{
			fmt::print(stderr, "Could not unregister '{}' file system: {}\n",
					   defaultFileSystems[i].name, uqm::strerror(errno));
		}
	}
}

// if wantedID = 0, just pick one
// if wantedID != 0, 0 will be returned if that id wasn't available
// a copy of 'name' is made
uio_FileSystemID
uio_registerFileSystem(uio_FileSystemID wantedID, const char* name,
					   uio_FileSystemHandler* handler)
{
	uio_FileSystemInfo** ptr;

	if (!uio_validFileSystemHandler(handler))
	{
		errno = EINVAL;
		return -1;
	}
	if (wantedID == 0)
	{
		// Search for the first free id >= uio_FIRST_CUSTOM_ID
		// it is put in wantedID

		for (ptr = &uio_fileSystems; *ptr != nullptr; ptr = &(*ptr)->next)
		{
			if ((*ptr)->id >= uio_FS_FIRST_CUSTOM_ID)
			{
				break;
			}
		}

		wantedID = uio_FS_FIRST_CUSTOM_ID;
		while (*ptr != nullptr)
		{
			if ((*ptr)->id != wantedID)
			{
				// wantedID is not in use
				break;
			}
			wantedID++;
			ptr = &(*ptr)->next;
		}
		// wantedID contains the new ID
	}
	else
	{
		// search for the place in the list where to insert the wanted
		// id, keeping the list sorted
		for (ptr = &uio_fileSystems; *ptr != nullptr; ptr = &(*ptr)->next)
		{
			if ((*ptr)->id <= wantedID)
			{
				if ((*ptr)->id == wantedID)
				{
					return 0;
				}
				break;
			}
		}
	}
	// ptr points to the place where the new link can inserted

	if (handler->init != nullptr && handler->init() == -1)
	{
		// errno is set
		return -1;
	}

	{
		uio_FileSystemInfo* newInfo;

		newInfo = uio_FileSystemInfo_new(wantedID, handler, uio_strdup(name));
		newInfo->next = *ptr;
		*ptr = newInfo;
		return wantedID;
	}
}

int uio_unRegisterFileSystem(uio_FileSystemID id)
{
	uio_FileSystemInfo** ptr;
	uio_FileSystemInfo* temp;

	ptr = uio_getFileSystemInfoPtr(id);
	if (ptr == nullptr)
	{
		errno = EINVAL;
		return -1;
	}
	if ((*ptr)->ref > 1)
	{
		errno = EBUSY;
		return -1;
	}

	if ((*ptr)->handler->unInit != nullptr && ((*ptr)->handler->unInit() == -1))
	{
		// errno is set
		return -1;
	}

	temp = *ptr;
	*ptr = (*ptr)->next;

	//	uio_FileSystemHandler_unref(temp->handler);
	uio_free(temp->name);
	uio_FileSystemInfo_free(temp);

	return 0;
}

static uio_bool
uio_validFileSystemHandler(uio_FileSystemHandler* handler)
{
	// Check for the essentials
	if (handler->mount == nullptr || handler->umount == nullptr || handler->open == nullptr || handler->close == nullptr || handler->read == nullptr || handler->openEntries == nullptr || handler->readEntries == nullptr || handler->closeEntries == nullptr)
	{
#ifdef DEBUG
		fmt::print(stderr, "Invalid file system handler.\n");
#endif
		return false;
	}
	return true;
}

uio_FileSystemHandler*
uio_getFileSystemHandler(uio_FileSystemID id)
{
	uio_FileSystemInfo* ptr;

	for (ptr = uio_fileSystems; ptr != nullptr; ptr = ptr->next)
	{
		if (ptr->id == id)
		{
			return ptr->handler;
		}
	}
	return nullptr;
}

uio_FileSystemInfo*
uio_getFileSystemInfo(uio_FileSystemID id)
{
	uio_FileSystemInfo* ptr;

	for (ptr = uio_fileSystems; ptr != nullptr; ptr = ptr->next)
	{
		if (ptr->id == id)
		{
			return ptr;
		}
	}
	return nullptr;
}

static uio_FileSystemInfo**
uio_getFileSystemInfoPtr(uio_FileSystemID id)
{
	uio_FileSystemInfo** ptr;

	for (ptr = &uio_fileSystems; *ptr != nullptr; ptr = &(*ptr)->next)
	{
		if ((*ptr)->id == id)
		{
			return ptr;
		}
	}
	return nullptr;
}

// sets ref to 1
static uio_FileSystemInfo*
uio_FileSystemInfo_new(uio_FileSystemID id, uio_FileSystemHandler* handler,
					   char* name)
{
	uio_FileSystemInfo* result;

	result = uio_FileSystemInfo_alloc();
	result->id = id;
	result->handler = handler;
	result->name = name;
	result->ref = 1;
	return result;
}

// *** Allocators ***

static inline uio_FileSystemInfo*
uio_FileSystemInfo_alloc(void)
{
	uio_FileSystemInfo* result = (uio_FileSystemInfo*)uio_malloc(sizeof(uio_FileSystemInfo));
#ifdef uio_MEM_DEBUG
	uio_MemDebug_debugAlloc(uio_FileSystemInfo, (void*)result);
#endif
	return result;
}


// *** Deallocators ***

static inline void
uio_FileSystemInfo_free(uio_FileSystemInfo* fileSystemInfo)
{
#ifdef uio_MEM_DEBUG
	uio_MemDebug_debugFree(uio_FileSystemInfo, (void*)fileSystemInfo);
#endif
	uio_free(fileSystemInfo);
}
