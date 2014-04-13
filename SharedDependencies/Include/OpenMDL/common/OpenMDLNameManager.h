/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_NAMEMANAGER_H_
#define _OPENMDL_COMMON_NAMEMANAGER_H_

#define OPENMDL_MAX_NAMES 1024

#include "../common/OpenMDLCommon.h"

namespace OpenMDL
{
	class OPENMDL_EXPORT_FUNCTION NameManager
	{
	public:
		static void					Clear(bool deleteitems = true);
		static void					Add(const char* name);

		static String*				GetNames();
		static bool					HasName(const char* name);
		static unsigned short		GetNameIndex(const char* name);
		static unsigned int			Size();
		static String&				GetName(unsigned short index);

	protected:
		static String				m_Names[OPENMDL_MAX_NAMES];
		static unsigned int			m_Top;
	};
}

#endif