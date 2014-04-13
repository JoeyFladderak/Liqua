#ifndef _SCENE_H_
#define _SCENE_H_

#include "RenderTarget.h"
#include "Shader.h"
#include "Light.h"
#include "Caustics.h"
#include "Shaft.h"
#include "WaterSurface.h"
#include "Sky.h"
#include "ParticleSystem.h"
#include "Mesh.h"
#include "School.h"
#include "Fish.h"

#define SHAFTS 60
#define DOFSAMPLES 64
#define PARTICLESYSTEMS 5

	class Scene
	{
	public:

		Scene();
		~Scene();

		void UpdateScene(float a_DT);
		void RenderScene();
		void FinalizeScene();

		void PassParameters(const glm::mat4 &a_Projection, const glm::mat4 &aA_View, const glm::vec3 &a_CamPos);
		void AddAffectedMesh(Liqua::Mesh* a_Mesh);

	protected:

		void RenderToTexture();

		Liqua::Mesh* m_Island;

 		glm::vec3 m_Ambient;
		glm::vec3 m_WaterColor;
 		Liqua::Light* m_SunLight;
 
 		glm::mat4 m_ProjectionMatrix;
 		glm::mat4 m_ViewMatrix;
 		glm::vec3 m_CamPos;
 
 		std::vector<Liqua::Mesh*> m_AffectedMeshes;
 
 		Liqua::Caustics* m_CausticsEffect;
 		Liqua::Shaft* m_Shaft[SHAFTS];
 		Liqua::WaterSurface* m_WaterSurface;
 		Liqua::Sky* m_Sky;
 		Liqua::ParticleSystem* m_ParticleSystem[PARTICLESYSTEMS];
 		Liqua::School* m_SchoolOfFish;
 
 		Liqua::RenderTarget* m_RenderTarget;
 		Liqua::Shader* m_DoFShader;
 		Liqua::Shader* m_ShaftShader;
 
 		GLfloat m_Quad[18];
 		GLuint m_QuadBuffer;
 
 		glm::vec2 m_Samples[DOFSAMPLES];
	};
#endif