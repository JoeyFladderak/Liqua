/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_WEIGHT_H_
#define _OPENMDL_COMMON_WEIGHT_H_

#include "OpenMDLMeshManager.h"
#include "OpenMDLJointManager.h"

namespace OpenMDL
{
	class Mesh;
	class Joint;

	class OPENMDL_EXPORT_FUNCTION Weight
	{
	public:
		Weight();
		Weight(unsigned int vertexId, float influence, unsigned int jointId);
		~Weight();

		unsigned int	GetVertexId() const;
		float			GetInfluence() const;
		unsigned int	GetJointId() const;

	protected:
		unsigned int	m_VertexId;
		float			m_Influence;
		unsigned int	m_JointId;
	};
}

#endif