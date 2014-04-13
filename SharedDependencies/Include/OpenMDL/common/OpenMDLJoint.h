/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_JOINT_H_
#define _OPENMDL_COMMON_JOINT_H_

#include "OpenMDLCommon.h"
#include "OpenMDLNode.h"

namespace OpenMDL
{
	class Weight;
	class OPENMDL_EXPORT_FUNCTION Joint : public Node
	{
		friend class Importer;
		friend class MayaCommon;
	public:
		Joint();
		Joint(const char* name, const matrix4x4& transform);
		virtual ~Joint();

		matrix4x4&			GetInverseBindPose();

	protected:
		matrix4x4			m_InvBindPose;
	};
}

#endif