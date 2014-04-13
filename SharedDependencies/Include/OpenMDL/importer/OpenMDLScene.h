/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_SCENE_H_
#define _OPENMDL_SCENE_H_

namespace OpenMDL
{
	class Mesh;
	class Camera;
	class Light;
	class Joint;
	class Material;
	class Transform;

	class OPENMDL_EXPORT_FUNCTION Scene
	{
		friend class Importer;
	public:
		Scene(String& name);
		~Scene();

		unsigned int			GetNodeCount();
		Node*					GetNode(unsigned int index);
		unsigned int			GetTransformCount();
		Transform*				GetTransform(unsigned int index);
		unsigned int			GetMeshCount();
		Mesh*					GetMesh(unsigned int index);
		unsigned int			GetJointCount();
		Joint*					GetJoint(unsigned int index);
		unsigned int			GetRootJointCount();
		Joint*					GetRootJoint(unsigned int index);
		unsigned int			GetMaterialCount();
		Material*				GetMaterial(unsigned int index);
		const char*				GetName();
		unsigned int			GetVersion();
		const char*				GetExporterName();
		bool					IsTriangulated();
		bool					HasInvertedU();
		bool					HasInvertedV();
		const char*				GetAnimationFile();
		unsigned int			GetAnimationCount();
		Animation*				GetAnimation(const char* name);
		Animation*				GetAnimation(unsigned int index);

	protected:
		NodeList				m_Nodes;
		TransformList			m_Transforms;
		MeshList				m_Meshes;
		JointList				m_Joints;
		MaterialList			m_Materials;
		JointList				m_RootJoints;
		unsigned int			m_Version;
		String					m_ExporterName;
		String					m_Name;
		String					m_AnimFile;
		bool					m_IsTriangulated;
		bool					m_InvertedU;
		bool					m_InvertedV;
		AnimationList			m_Animations;
	};
}

#endif