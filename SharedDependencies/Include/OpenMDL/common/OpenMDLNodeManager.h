/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_NODEMANAGER_H_
#define _OPENMDL_COMMON_NODEMANAGER_H_

#include "../common/OpenMDLCommon.h"

namespace OpenMDL
{
	class Node;
	class OPENMDL_EXPORT_FUNCTION NodeManager
	{
	public:
		static void					Clear(bool deleteitems = true);
		static void					Add(Node* node);
		static void					Remove(Node* node);
		static void					Remove(const char* name);

		static NodeList&			GetNodes();
		static OpenMDL::Node*		GetNode(const char* name, unsigned int typemask = 0);

	protected:
		static NodeList				m_Nodes;
	};
}

#endif