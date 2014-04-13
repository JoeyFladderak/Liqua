/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_MESHMANAGER_H_
#define _OPENMDL_COMMON_MESHMANAGER_H_

#include "../common/OpenMDLCommon.h"

namespace OpenMDL
{
	class Mesh;
	class OPENMDL_EXPORT_FUNCTION MeshManager
	{
	public:
		static void					Clear(bool deleteitems = true);
		static void					Add(Mesh* mesh);
		static void					Remove(Mesh* mesh);
		static void					Remove(const char* name);

		static MeshList&			GetMeshes();
		static OpenMDL::Mesh*		GetMesh(const char* name);

	protected:
		static MeshList				m_Meshes;
	};
}

#endif