/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_STREAM_H_
#define _OPENMDL_STREAM_H_

#include "OpenMDLcommon.h"

namespace OpenMDL
{
	class OPENMDL_EXPORT_FUNCTION Stream
	{
	public:
		static void			Write(void* a_Buffer, unsigned int a_Size);
		static void			Write(const void* a_Buffer, unsigned int a_Size);
		static void			Read(void* a_Buffer, unsigned int a_Size);
		static bool			Open(String& a_File, const char* a_Mode);
		static bool			Close();

		static FILE*		GetFp();
		static bool			HasFp();
		static long long	GetPosition();

	protected:
		static FILE*		m_Fp;
		static String		m_File;
	};
}
#endif