/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_MATERIALMANAGER_H_
#define _OPENMDL_COMMON_MATERIALMANAGER_H_

#include "../common/OpenMDLCommon.h"

namespace OpenMDL
{
	class Material;
	class OPENMDL_EXPORT_FUNCTION MaterialManager
	{
	public:
		static void						Clear(bool deleteitems = true);
		static void						Add(Material* material);
		static void						Remove(Material* material);
		static void						Remove(const char* name);

		static MaterialList&			GetMaterials();
		static OpenMDL::Material*		GetMaterial(const char* name);
		static OpenMDL::Material*		GetMaterial(unsigned int index);
		static unsigned short			GetMaterialIndex(const char* name);

	protected:
		static MaterialList				m_Materials;
	};
}

#endif