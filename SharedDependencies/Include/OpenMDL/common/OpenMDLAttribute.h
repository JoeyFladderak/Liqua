/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_ATTRIBUTE_H_
#define _OPENMDL_COMMON_ATTRIBUTE_H_

#include "OpenMDLCommon.h"

namespace OpenMDL
{
	class OPENMDL_EXPORT_FUNCTION Attribute
	{
	public:
		Attribute(const char* name, AttributeType type, void* data, unsigned int datasize);
		~Attribute();
		
		String&					GetName();
		AttributeType			GetType() const;
		unsigned char*			GetData() const;
		unsigned int			GetSize() const;

		int						GetInt();
		float					GetFloat();
		bool					GetBoolean();
		OpenMDL::String			GetString();
		OpenMDL::float3			GetFloat3();

	protected:
		String					m_Name;
		AttributeType			m_Type;
		unsigned char*			m_Data;
		unsigned int			m_Size;
	};
}

#endif