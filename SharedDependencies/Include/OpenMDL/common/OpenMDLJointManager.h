/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_JOINTMANAGER_H_
#define _OPENMDL_COMMON_JOINTMANAGER_H_

#include "../common/OpenMDLCommon.h"

namespace OpenMDL
{
	class Joint;
	class OPENMDL_EXPORT_FUNCTION JointManager
	{
	public:
		static void						Clear(bool deleteitems = true);
		static void						Add(Joint* joint);
		static void						Remove(Joint* joint);
		static void						Remove(const char* name);

		static JointList&				GetJoints();
		static OpenMDL::Joint*			GetJoint(const char* name);
		static unsigned int				GetJointIndex(const char* name);

	protected:
		static JointList				m_Joints;
	};
}

#endif