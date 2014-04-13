/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_VERTEXGROUP_H_
#define _OPENMDL_VERTEXGROUP_H_

namespace OpenMDL
{
	class Material;
	class OPENMDL_EXPORT_FUNCTION FaceGroup
	{
		friend class Importer;
		friend class MayaCommon;
		friend class MayaExporter;
	public:
		FaceGroup();
		FaceGroup(Material* material);
		~FaceGroup();

		Material*				GetMaterial() const;
		unsigned int			GetFaceCount() const;
		unsigned int			GetIndexCount() const;
		unsigned int			GetVertexIndex(unsigned int index) const;
		unsigned int			GetNormalIndex(unsigned int index) const;
		unsigned int			GetTangentIndex(unsigned int index) const;
		unsigned int			GetUVIndex(unsigned int index, unsigned int layer = 0) const;
		unsigned int			GetWeightIndex(unsigned int index) const;
		
		Weight**				GetWeightsByVertexId(unsigned int vertexId, OpenMDL::Mesh* mesh, unsigned int* out_weightCount);

	protected:
		Material*				m_Material;
		unsigned int			m_IndexCount;
		unsigned int			m_FaceCount;
		UIntList				m_PointIndices;
		UIntList				m_NormalIndices;
		UIntList				m_TangentIndices;
		UIntList				m_WeightIndices;
		UVIndexSetList			m_UVIndices;
	};
}

#endif