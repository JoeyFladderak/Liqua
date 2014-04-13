/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_JOINTPOSE_H_
#define _OPENMDL_COMMON_JOINTPOSE_H_

namespace OpenMDL
{
	class Joint;

	class OPENMDL_EXPORT_FUNCTION JointPose
	{
		friend class Importer;
		friend class MayaCommon;
	public:
		JointPose();
		JointPose(unsigned short jointId, float3& translation, float4& rotation, float3& scale);
		~JointPose();

		unsigned short		GetJointId() const;
		float3&				GetTranslation();
		float4&				GetRotation();
		float3&				GetScale();

	protected:
		unsigned short		m_JointId;
		float3				m_Translation;
		float4				m_Rotation;
		float3				m_Scale;
	};
}

#endif