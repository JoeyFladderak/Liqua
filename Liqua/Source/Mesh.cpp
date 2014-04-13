#include "Liqua.h"
#include "Shader.h"
#include "Mesh.h"

#define POSITION_ATTRIBUTE 0
#define TEXCOORD0_ATTRIBUTE 1
#define NORMAL_ATTRIBUTE 2
#define DIFFUSE_ATTRIBUTE 3
#define TANGENT_ATTRIBUTE 4
#define BINORMAL_ATTRIBUTE 5

#define MEMBER_OFFSET(s,m) ((char *)NULL + (offsetof(s,m)))
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Liqua::Mesh::Mesh(std::string a_File)
{
	Load(a_File);
	m_ModelMatrix = glm::mat4(1);
	m_Shader = NULL;
}

Liqua::Mesh::Mesh()
{
	m_ModelMatrix = glm::mat4(1);
	m_Shader = NULL;
}

Liqua::Mesh::~Mesh()
{
	if(m_VAO != 0)
	{
		glDeleteVertexArrays(1, &m_VAO);
	}

	for(unsigned int i = 0; i < m_FaceGroupList.size(); i++)
	{
		if(m_FaceGroupList[i].m_VertexBuffer != 0)
		{
			glDeleteBuffers(1, &m_FaceGroupList[i].m_VertexBuffer);
		}
	}
}

void Liqua::Mesh::Load( std::string a_File )
{
	m_Scene = OpenMDL::Importer::GetSingleton()->LoadScene((a_File).c_str());

	unsigned int meshcount = m_Scene->GetMeshCount();
	for(unsigned int i = 0; i < meshcount; ++i)
	{
		OpenMDL::Mesh* mesh = m_Scene->GetMesh(i);
		unsigned int FGcount = mesh->GetFaceGroupCount();
		for(unsigned int j = 0; j < FGcount; ++j)
		{
			OpenMDL::FaceGroup* facegroup = mesh->GetFaceGroup(j);
			FaceGroup tmpFG;
			unsigned int indexcount = facegroup->GetIndexCount();
			for(unsigned int k = 0; k < indexcount; ++k)
			{
				unsigned int vertexIndex = facegroup->GetVertexIndex(k);
				unsigned int normalIndex = facegroup->GetNormalIndex(k);
				unsigned int uvIndex = facegroup->GetUVIndex(k);
				unsigned int tangentindex = facegroup->GetTangentIndex(k);


				OpenMDL::float3* vert = mesh->GetPoint(vertexIndex);
				OpenMDL::float3* normal = mesh->GetNormal(normalIndex);
				OpenMDL::float2* uv = mesh->GetUV(uvIndex);
				OpenMDL::float3* binormal = mesh->GetBinormal(normalIndex);
				OpenMDL::float3* tangent = mesh->GetTangent(tangentindex);

				Vertex myvert;

				myvert.m_Position.x = vert->x;
				myvert.m_Position.y = vert->y;
				myvert.m_Position.z = vert->z;

				if(normal)
				{
					myvert.m_Normal.x = normal->x;
					myvert.m_Normal.y = normal->y;
					myvert.m_Normal.z = normal->z;
				}

				if(uv)
				{
					myvert.m_UV.x = uv->u;
					myvert.m_UV.y = uv->v;
				}

				if(binormal)
				{
					myvert.m_BiNormal.x = binormal->x;
					myvert.m_BiNormal.y = binormal->y;
					myvert.m_BiNormal.z = binormal->z;
				}

				if(tangent)
				{
					myvert.m_Tangent.x = tangent->x;
					myvert.m_Tangent.y = tangent->y;
					myvert.m_Tangent.z = tangent->z;
				}

				tmpFG.m_Vertices.push_back(myvert);
			}

			OpenMDL::Material* mat = facegroup->GetMaterial();
			tmpFG.m_MatName = mat->GetName().GetBuffer();
			m_FaceGroupList.push_back(tmpFG);
		}
	}

	LoadMaterials();

	glGenVertexArrays(1, &m_VAO); //CheckGL();
	glBindVertexArray(m_VAO); //CheckGL();

	for(unsigned int i = 0; i < m_FaceGroupList.size(); ++i)
	{
		glGenBuffers(1, &m_FaceGroupList[i].m_VertexBuffer);// CheckGL();	
		glBindBuffer(GL_ARRAY_BUFFER, m_FaceGroupList[i].m_VertexBuffer);// CheckGL();

		glBufferData(GL_ARRAY_BUFFER, m_FaceGroupList[i].m_Vertices.size() * sizeof(Vertex), &(m_FaceGroupList[i].m_Vertices[0]), GL_STATIC_DRAW);// CheckGL();

		glVertexAttribPointer(POSITION_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), MEMBER_OFFSET(Vertex, m_Position));// CheckGL();
		glEnableVertexAttribArray(POSITION_ATTRIBUTE); //CheckGL();

		glVertexAttribPointer(NORMAL_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), MEMBER_OFFSET(Vertex, m_Normal));// CheckGL();
		glEnableVertexAttribArray(NORMAL_ATTRIBUTE); //CheckGL();

		glVertexAttribPointer(TANGENT_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), MEMBER_OFFSET(Vertex, m_Tangent));// CheckGL();
		glEnableVertexAttribArray(TANGENT_ATTRIBUTE); //CheckGL();

		glVertexAttribPointer(BINORMAL_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), MEMBER_OFFSET(Vertex, m_BiNormal)); //CheckGL();
		glEnableVertexAttribArray(BINORMAL_ATTRIBUTE); //CheckGL();

		glVertexAttribPointer(TEXCOORD0_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), MEMBER_OFFSET(Vertex, m_UV));// CheckGL();
		glEnableVertexAttribArray(TEXCOORD0_ATTRIBUTE); //CheckGL();

		BindMaterial(m_FaceGroupList[i].m_MatName, i);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0); //CheckGL();
	glBindVertexArray(0); //CheckGL();
}

void Liqua::Mesh::RenderFaceGroup( const FaceGroup& a_FaceGroup )
{
	unsigned int texid = 0;

	if(m_Shader != NULL)
	{
		m_Shader->Bind();

		m_Shader->SetUniform3f("AmbientColor", glm::value_ptr(m_MaterialList[a_FaceGroup.m_MatID].m_Ambient));

		if(m_MaterialList[a_FaceGroup.m_MatID].m_DiffuseMap != 0)
		{
			texid = m_MaterialList[a_FaceGroup.m_MatID].m_DiffuseMap;
			glActiveTexture(GL_TEXTURE0); CheckGL();
			m_Shader->SetUniform1i("DiffuseMap", 0);
			glBindTexture(GL_TEXTURE_2D, texid); CheckGL();
		}
		else
		{
			m_Shader->SetUniform3f("DiffuseColor", glm::value_ptr(m_MaterialList[a_FaceGroup.m_MatID].m_Diffuse));
		}

		if(m_MaterialList[a_FaceGroup.m_MatID].m_SpecularMap != 0)
		{
			texid = m_MaterialList[a_FaceGroup.m_MatID].m_SpecularMap;
			glActiveTexture(GL_TEXTURE2); CheckGL();
			m_Shader->SetUniform1i("SpecularMap", 2);
			glBindTexture(GL_TEXTURE_2D, texid); CheckGL();
		}
		else
		{
			m_Shader->SetUniform3f("SpecularColor", glm::value_ptr(m_MaterialList[a_FaceGroup.m_MatID].m_Specular));
			m_Shader->SetUniform1f("Shininess", m_MaterialList[a_FaceGroup.m_MatID].m_Shininess);
		}

		glDrawArrays(GL_TRIANGLES, 0, a_FaceGroup.m_Vertices.size()); //CheckGL();

		m_Shader->Unbind();

		glBindTexture(GL_TEXTURE_2D, 0); CheckGL();
	}
}

void Liqua::Mesh::Render()
{
	m_ModelMatrix = m_Pos * m_Rot * m_Scale;

	glBindVertexArray(m_VAO);

	for(unsigned int i = 0; i < m_FaceGroupList.size(); i++)
	{
		RenderFaceGroup(m_FaceGroupList[i]);
	}

	glBindVertexArray(0);
}

void Liqua::Mesh::LoadMaterials()
{
	unsigned int matcount = m_Scene->GetMaterialCount();
	for(unsigned int i = 0; i < matcount; ++i)
	{
		OpenMDL::Material* mat = m_Scene->GetMaterial(i);
		Material tmpmat;

		tmpmat.m_Name = mat->GetName().GetBuffer();
		tmpmat.m_ID = i;

		if(mat->GetDiffuseMap().GetBuffer())
		{
			char tmp[256];
			sprintf_s(tmp, "../Resources/Textures/Models/%s", mat->GetDiffuseMap().GetBuffer());
			unsigned int id = SOIL_load_OGL_texture(tmp, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
			tmpmat.m_DiffuseMap = id;
		}

		if(mat->GetSpecularMap().GetBuffer())
		{
			char tmp[256];
			sprintf_s(tmp, "../Resources/Textures/Models/%s", mat->GetSpecularMap().GetBuffer());
			unsigned int id = SOIL_load_OGL_texture(tmp, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
			tmpmat.m_SpecularMap = id;
		}

		if(mat->GetNormalMap().GetBuffer())
		{
			char tmp[256];
			sprintf_s(tmp, "../Resources/Textures/Models/%s", mat->GetNormalMap().GetBuffer());
			unsigned int id = SOIL_load_OGL_texture(tmp, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
			tmpmat.m_NormalMap = id;
		}

		if(mat->GetEmissiveMap().GetBuffer())
		{
			char tmp[256];
			sprintf_s(tmp, "../Resources/Textures/Models/%s", mat->GetEmissiveMap().GetBuffer());
			unsigned int id = SOIL_load_OGL_texture(tmp, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
			tmpmat.m_EmissiveMap = id;
		}

		if((mat->GetAmbientColor().r + mat->GetAmbientColor().g + mat->GetAmbientColor().b) > 0)
		{
			tmpmat.m_Ambient.r = mat->GetAmbientColor().r;
			tmpmat.m_Ambient.g = mat->GetAmbientColor().g;
			tmpmat.m_Ambient.b = mat->GetAmbientColor().b;
		}

		if((mat->GetDiffuseColor().r + mat->GetDiffuseColor().g + mat->GetDiffuseColor().b) > 0)
		{
			tmpmat.m_Diffuse.r = mat->GetDiffuseColor().r;
			tmpmat.m_Diffuse.g = mat->GetDiffuseColor().g;
			tmpmat.m_Diffuse.b = mat->GetDiffuseColor().b;
		}

		if((mat->GetSpecularColor().r + mat->GetSpecularColor().g + mat->GetSpecularColor().b) > 0)
		{
			tmpmat.m_Specular.r = mat->GetSpecularColor().r;
			tmpmat.m_Specular.g = mat->GetSpecularColor().g;
			tmpmat.m_Specular.b = mat->GetSpecularColor().b;
		}

		if((mat->GetEmissiveColor().r + mat->GetEmissiveColor().g + mat->GetEmissiveColor().b) > 0)
		{
			tmpmat.m_Emissive.r = mat->GetEmissiveColor().r;
			tmpmat.m_Emissive.g = mat->GetEmissiveColor().g;
			tmpmat.m_Emissive.b = mat->GetEmissiveColor().b;
		}

		if(mat->GetSpecularCoeff() > 0)
			tmpmat.m_Shininess = mat->GetSpecularCoeff();

		m_MaterialList.push_back(tmpmat);
	}
}

void Liqua::Mesh::BindMaterial( std::string a_Name, unsigned int a_FaceGroup )
{
	for(unsigned int i = 0; i < m_MaterialList.size(); ++i)
	{
		if(m_MaterialList[i].m_Name.compare(a_Name) == 0)
		{
			m_FaceGroupList[a_FaceGroup].m_MatID = m_MaterialList[i].m_ID;
		}
	}
}

void Liqua::Mesh::SetShader( Shader* a_Shader )
{
	if(a_Shader == m_Shader)
		return;

	m_Shader = a_Shader;
}

void Liqua::Mesh::Translate( glm::vec3 a_Amount )
{
	m_Pos = glm::translate(a_Amount);
}

void Liqua::Mesh::Scale( glm::vec3 a_Scale )
{
	m_Scale = glm::scale(a_Scale);
}

void Liqua::Mesh::Rotate( float a_Angle, glm::vec3 a_Axis )
{
	if(a_Axis.x == 1)
		m_RotX = glm::rotate(a_Angle, a_Axis);

	if(a_Axis.y == 1)
		m_RotY = glm::rotate(a_Angle, a_Axis);

	if(a_Axis.z == 1)
		m_RotZ = glm::rotate(a_Angle, a_Axis);

	m_Rot = m_RotX * m_RotY * m_RotZ;
}

void Liqua::Mesh::Rotate( glm::quat& a_Rotation )
{
	m_Rot = glm::toMat4(a_Rotation);
}

void Liqua::Mesh::Update( float a_DT )
{

}