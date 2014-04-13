/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_MESH_H_
#define _OPENMDL_COMMON_MESH_H_

#include "OpenMDLcommon.h"
#include "OpenMDLNode.h"

namespace OpenMDL
{
	class FaceGroup;
	class OPENMDL_EXPORT_FUNCTION Mesh : public Node
	{
		friend class Importer;
		friend class MayaCommon;
		friend class MayaExporter;
	public:
		Mesh();
		Mesh(const char* name, const matrix4x4& transform);
		virtual ~Mesh();

		unsigned int			GetFaceGroupCount() const;
		FaceGroup*				GetFaceGroup(unsigned int index) const;
		FaceGroup*				AddMaterial(Material* material);
		unsigned int			GetMaterialCount() const;
		Material*				GetMaterial(unsigned int index = 0) const;
		unsigned int			GetPointCount() const;
		float3*					GetPoint(unsigned int index) const;
		unsigned int			GetNormalCount() const;
		float3*					GetNormal(unsigned int index) const;
		unsigned int			GetTangentCount() const;
		float3*					GetBinormal(unsigned int index) const;
		float3*					GetTangent(unsigned int index) const;
		unsigned int			GetUVSetCount() const;
		unsigned int			GetUVCount(unsigned int layer = 0) const;
		float2*					GetUV(unsigned int index, unsigned int layer = 0) const;
		unsigned int			GetWeightCount() const;
		Weight*					GetWeight(unsigned int index) const;

	protected:
		FaceGroupList			m_FaceGroups;
		Float3List				m_Points;
		Float3List				m_Normals;
		Float3List				m_Binormals;
		Float3List				m_Tangents;
		UVSetList				m_UVSets;
		WeightList				m_Weights;
	};
}

#endif