#ifndef _MESH_H_
#define _MESH_H_

#include "FaceGroup.h"
#include "Material.h"
#include "OpenMDL/importer/OpenMDL.h"

namespace Liqua
{
	class Shader;
	class LIQUAEXPORT Mesh
	{
	public:

		Mesh();
		Mesh(std::string a_File); 
		~Mesh();

		void Load(std::string a_File);
		void Render();
		void SetShader(Shader* a_Shader);

		void Update(float a_DT);

		void Translate(glm::vec3 a_Amount);

		void Rotate(float a_Angle, glm::vec3 a_Axis);
		void Rotate(glm::quat& a_Rotation);

		void Scale(glm::vec3 a_Scale); 		

		glm::mat4 GetModelMatrix() {return m_ModelMatrix;} // pass by reference

	protected:

		void RenderFaceGroup(const FaceGroup& a_FaceGroup);
		void LoadMaterials();
		void BindMaterial(std::string a_Name, unsigned int a_FaceGroup);

		unsigned int m_VAO;

		glm::mat4 m_ModelMatrix;

		glm::mat4 m_Rot;
		glm::mat4 m_Pos;
		glm::mat4 m_Scale;

		glm::mat4 m_RotX;
		glm::mat4 m_RotY;
		glm::mat4 m_RotZ;

		std::vector<FaceGroup> m_FaceGroupList;
		std::vector<Material> m_MaterialList;

		std::vector<std::pair<std::string, unsigned int>> m_TextureList;

		OpenMDL::Scene* m_Scene;

		Shader* m_Shader;
	};
}

#endif