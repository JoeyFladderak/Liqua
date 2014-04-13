/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_ANIMATIONFRAME_H_
#define _OPENMDL_COMMON_ANIMATIONFRAME_H_

namespace OpenMDL
{
	class OPENMDL_EXPORT_FUNCTION AnimationFrame
	{
		friend class Importer;
		friend class MayaCommon;
		friend class MayaExporter;
	public:
		AnimationFrame();
		~AnimationFrame();

		unsigned int		GetJointPoseCount() const;
		JointPose*			GetJointPose(unsigned int index) const;

	protected:
		JointPoseList		m_JointPoses;
		TransformPoseList	m_TransformPoses;
	};
}

#endif