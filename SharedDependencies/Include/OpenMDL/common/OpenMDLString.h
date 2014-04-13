/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_STRING_H_
#define _OPENMDL_COMMON_STRING_H_

#define OPENMDL_STRING_STEPSIZE 32

namespace OpenMDL
{
	class OPENMDL_EXPORT_FUNCTION String
	{
	public:
		String();
		String(const char* str);
		~String();

		const char*				GetBuffer() const;
		unsigned int			GetLength() const;

		void operator			+= (const String& str);
		void operator			+= (const char* str);
		void operator			= (const String& str);
		void operator			= (const char* str);

		const String& operator	+ (const String& str) const;
		const String& operator	+ (const char* str) const;

		bool operator			== (const String& str) const;
		bool operator			== (const char* str) const;
		bool operator			!= (const String& str) const;
		bool operator			!= (const char* str) const;

		char operator			[] (unsigned int i) const;

		operator char*()		{ return m_Buffer; }
		operator const char*()	{ return m_Buffer; }

		bool					EndsWith(const String& str) const;
		bool					EndsWith(const char* str) const;
		bool					StartsWith(const String& str) const;
		bool					StartsWith(const char* str) const;
		bool					Contains(const String& str) const;
		bool					Contains(const char* str) const;

		void					Clear();
		void					Delete();

	protected:
		char*					m_Buffer;
		unsigned int			m_Length;
		unsigned int			m_BufferSize;
	};
}

#endif