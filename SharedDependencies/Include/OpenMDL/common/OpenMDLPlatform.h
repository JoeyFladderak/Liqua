/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_PLATFORM_H_
#define _OPENMDL_COMMON_PLATFORM_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#ifdef OPENMDL_MAYA
#	include <string>
#endif

#ifdef OPENMDL_WINDOWS
#	define OPENMDL_IGNORE				0
#	define OPENMDL_INFINITE				0xFFFFFFFF
#	define OPENMDL_ZEROMEMORY(mem, len)	memset(mem, 0, len)
#	define OPENMDL_MSGBOX(title, msg)	MessageBoxA(0, msg, title, MB_OK);

#	include <windows.h>
#endif

#ifdef OPENMDL_OSX
#	define OPENMDL_IGNORE				0
#	define OPENMDL_INFINITE				0xFFFFFFFF
#	define OPENMDL_ZEROMEMORY(mem, len)	memset(mem, 0, len)
#	define OPENMDL_MSGBOX(title, msg)	
#endif

#ifdef OPENMDL_LINUX
#	define OPENMDL_IGNORE				0
#	define OPENMDL_INFINITE				0xFFFFFFFF
#	define OPENMDL_ZEROMEMORY(mem, len)	memset(mem, 0, len)
#	define OPENMDL_MSGBOX(title, msg)	
#endif

#endif