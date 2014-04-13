/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_ANIMATIONMANAGER_H_
#define _OPENMDL_COMMON_ANIMATIONMANAGER_H_

#include "../common/OpenMDLCommon.h"

namespace OpenMDL
{
	class Animation;
	class OPENMDL_EXPORT_FUNCTION AnimationManager
	{
	public:
		static void					Clear(bool deleteitems = true);
		static void					Add(Animation* anim);
		static void					Remove(Animation* anim);
		static void					Remove(const char* name);

		static AnimationList&		GetAnimations();
		static OpenMDL::Animation*	GetAnimation(const char* name);

	protected:
		static AnimationList				m_Animations;
	};
}
#endif