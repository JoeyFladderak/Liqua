 #ifndef _FACEGROUP_H_
 #define _FACEGROUP_H_

struct Vertex
{
	glm::vec3 m_Position;
	glm::vec3 m_Normal;
	glm::vec3 m_Tangent;
	glm::vec3 m_BiNormal;
	glm::vec2 m_UV;
};
 
 namespace Liqua
 {
 	class LIQUAEXPORT FaceGroup
 	{
 	public:
 
 		FaceGroup();
 		~FaceGroup();
 
 		std::string m_MatName;
 		unsigned int m_MatID;
 
 		std::vector<Vertex> m_Vertices;
 		unsigned int m_VertexBuffer;
 	};
 }
 
 #endif