/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_TRANSFORM_H_
#define _OPENMDL_COMMON_TRANSFORM_H_

#include "OpenMDLCommon.h"
#include "OpenMDLNode.h"

namespace OpenMDL
{
	class OPENMDL_EXPORT_FUNCTION Transform : public Node
	{
	public:
		Transform();
		Transform(const char* name, const matrix4x4& transform);
		virtual ~Transform();

	protected:

	};
}

#endif