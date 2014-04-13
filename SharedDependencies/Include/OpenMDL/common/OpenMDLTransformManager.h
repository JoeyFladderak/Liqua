/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_TRANSFORMMANAGER_H_
#define _OPENMDL_COMMON_TRANSFORMMANAGER_H_

#include "../common/OpenMDLCommon.h"

namespace OpenMDL
{
	class Transform;
	class OPENMDL_EXPORT_FUNCTION TransformManager
	{
	public:
		static void							Clear(bool deleteitems = true);
		static void							Add(Transform* transform);
		static void							Remove(Transform* transform);
		static void							Remove(const char* name);

		static TransformList&				GetTransforms();
		static OpenMDL::Transform*			GetTransform(const char* name);
		static unsigned short				GetTransformIndex(const char* name);

	protected:
		static TransformList				m_Transforms;
	};
}

#endif