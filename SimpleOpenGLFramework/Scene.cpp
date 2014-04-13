#include "Liqua.h"
#include "Scene.h"

Scene::Scene()
{
	// Creating the rendertarget and corresponding plane.
 	m_RenderTarget = new Liqua::RenderTarget(SCRWIDTH, SCRHEIGHT, 1);
 
 	m_Quad[0]  = -1.0f; m_Quad[1]  = -1.0f; m_Quad[2]  = 0.0f;
 	m_Quad[3]  =  1.0f; m_Quad[4]  = -1.0f; m_Quad[5]  = 0.0f;
 	m_Quad[6]  = -1.0f; m_Quad[7]  =  1.0f; m_Quad[8]  = 0.0f;
 	m_Quad[9]  = -1.0f; m_Quad[10] =  1.0f; m_Quad[11] = 0.0f;
 	m_Quad[12] =  1.0f; m_Quad[13] = -1.0f; m_Quad[14] = 0.0f;
 	m_Quad[15] =  1.0f; m_Quad[16] =  1.0f; m_Quad[17] = 0.0f;
 
 	glGenBuffers(1, &m_QuadBuffer);
 	glBindBuffer(GL_ARRAY_BUFFER, m_QuadBuffer);
 	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Quad), m_Quad, GL_STATIC_DRAW);
 
	// create the depth of field shader
 	m_DoFShader = new Liqua::Shader();
 	m_DoFShader->CreateShader();
 	m_DoFShader->AttachVertexShader("../Resources/Shaders/DoF.vert");
 	m_DoFShader->AttachFragmentShader("../Resources/Shaders/DoF.frag");
 	m_DoFShader->LinkShader();
 
	// create the shader the shafts will use.
	m_ShaftShader = new Liqua::Shader();
	m_ShaftShader->CreateShader();
	m_ShaftShader->AttachVertexShader("../Resources/Shaders/Shaft.vert");
	m_ShaftShader->AttachFragmentShader("../Resources/Shaders/Shaft.frag");
	m_ShaftShader->LinkShader();

	// Set the ambient color
	m_Ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	// and the color of the water.
	m_WaterColor = glm::vec3(0.0f, 0.62f, 0.79f);

	// Light that acts as the sun
	m_SunLight = new Liqua::Light();
	m_SunLight->SetPosition(glm::vec3(0.1, 900, 0.1));

	// create the caustics effect
 	m_CausticsEffect = new Liqua::Caustics();
 
	// and load the textures for the caustic map
 	for(int i = 0; i <= 60; i++)
 	{
 		char temp[256];
 		int picindex = i + 1;
 		sprintf_s(temp, "../Resources/Textures/Caustics/CausticsRender_%03d.bmp", picindex);
 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 		GLuint id = SOIL_load_OGL_texture(temp, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
 		m_CausticsEffect->AddCausticTexture(id);
 	}
 
	// Create the shafts with their initial values
 	for(int i = 0; i < SHAFTS; i+=2)
 	{
 		float width = MathHelper::rFloatRange(25, 50);
 		float depth = MathHelper::rFloatRange(25, 50);
 		float angle = MathHelper::rFloatRange(0, 180);
 		glm::vec3 pos = glm::vec3(MathHelper::rFloatRange(50, 400), -2, MathHelper::rFloatRange(-200, 200));
 
 		m_Shaft[i] = new Liqua::Shaft((depth * (pos.x / 100)), width);
 
 		glm::quat Y = glm::angleAxis(angle, glm::vec3(0, 1, 0));
 		glm::quat X = glm::angleAxis(20.0f, glm::vec3(1, 0, 0));
 
 		glm::quat orientation = X * Y;
 
 		m_Shaft[i]->Rotate(orientation);
 		m_Shaft[i]->Translate(pos);
 		m_Shaft[i]->SetShader(m_ShaftShader);
 
 		m_Shaft[i]->SetStartPulse(MathHelper::rFloatRange(0.0f, 1.0f));
 		m_Shaft[i]->SetPulseFactor(MathHelper::rFloatRange(0.5f, 0.75f));
 		m_Shaft[i]->SetScrollSpeed(MathHelper::rFloatRange(-0.02f, 0.02f));
 
 		m_Shaft[i+1] = new Liqua::Shaft((depth * (pos.x / 100)), width);
 		m_Shaft[i+1]->Rotate(orientation);
 		m_Shaft[i+1]->Translate(pos);
 		m_Shaft[i+1]->SetShader(m_ShaftShader);
 
 		m_Shaft[i+1]->SetStartPulse(MathHelper::rFloatRange(0.0f, 1.0f));
 		m_Shaft[i+1]->SetPulseFactor(MathHelper::rFloatRange(0.5f, 0.75f));
 		m_Shaft[i+1]->SetScrollSpeed(MathHelper::rFloatRange(-0.02f, 0.02f));
 	}
 
	// Create the water surface
 	m_WaterSurface = new Liqua::WaterSurface();
	m_WaterSurface->SetHeight(-0.5);
	// and the sky
	m_Sky = new Liqua::Sky();

	// Create the particle systems with 400 particles each.
 	for(int i = 0; i < PARTICLESYSTEMS; i++)
 	{
 		m_ParticleSystem[i] = new Liqua::ParticleSystem(400);
 		char tmp[256];
 		sprintf_s(tmp, "../Resources/Textures/Particles/debris_%i.png", i);
 		int texid = SOIL_load_OGL_texture(tmp, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
 		m_ParticleSystem[i]->SetTexture(texid);
 	}
 
	// Create a school of fish with 10 fish in it
 	m_SchoolOfFish = new Liqua::School(10);
 
 	m_AffectedMeshes.clear();
 
	// Create the samples for the depth of field
 	for(unsigned int i = 0; i < DOFSAMPLES; i++)
 	{
 		m_Samples[i] = glm::vec2(MathHelper::rFloatRange(-0.002f, 0.002f), MathHelper::rFloatRange(-0.002f, 0.002f));
 	}
 
	// Add the fishes from the previously created school to a vector that handles meshes that are affected by caustics.
  	for(unsigned int i = 0; i < m_SchoolOfFish->GetFishArray().size(); i++)
  	{
  		AddAffectedMesh(m_SchoolOfFish->GetFishArray()[i]->GetMesh());
  	}
 
	// load the island and add it the same way as the fishes.
 	m_Island = new Liqua::Mesh("../Resources/Models/Island/Island.omd");
 	
 	AddAffectedMesh(m_Island);
}

Scene::~Scene()
{
	// cleaning up
 	delete m_SunLight;
 	delete m_DoFShader;
 	delete m_ShaftShader;
 	delete m_CausticsEffect;
 	delete m_WaterSurface;
 	delete m_Sky;
	for(unsigned int i = 0; i < 5; i++)
	{
 		delete m_ParticleSystem[i];
	}
 	delete m_SchoolOfFish;
 
 	for(unsigned int i = 0; i < SHAFTS; i++)
 	{
 		delete m_Shaft[i];
 	}
 
 	for(unsigned int i = 0; i < m_AffectedMeshes.size(); i++)
 	{
 		delete m_AffectedMeshes[i];
 	}
}

void Scene::UpdateScene( float a_DT )
{
	// call the update functions of all the effects.
	m_CausticsEffect->Update(a_DT);

	m_Sky->Update(a_DT);

	for(unsigned int i = 0; i < PARTICLESYSTEMS; i++)
	{
		m_ParticleSystem[i]->Update(a_DT);
	}

	m_WaterSurface->Update(a_DT);

	for(int i = 0; i < SHAFTS; i++)
	{
		m_Shaft[i]->Update(a_DT, m_CamPos);
	}

	m_SchoolOfFish->Update(a_DT);

	for(unsigned int i = 0; i < m_AffectedMeshes.size(); i++)
	{
		m_AffectedMeshes[i]->Update(a_DT);
	}
}

void Scene::RenderScene()
{
	// Clearing the background
	glClearColor( m_WaterColor.r, m_WaterColor.g, m_WaterColor.b, 1.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// activate rendertarget to render to and render all needed objects.
 	m_RenderTarget->Activate();
 	{
		// clearing the rendertarget
 		glClearColor(  m_WaterColor.r, m_WaterColor.g, m_WaterColor.b, 1.0f  );
 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
		m_Sky->PassParameters(m_ProjectionMatrix, m_ViewMatrix, m_CamPos, m_SunLight, m_WaterColor);
  		m_Sky->Render();		
  
   		m_WaterSurface->PassParameters(m_ProjectionMatrix, m_ViewMatrix, m_CamPos, m_SunLight, m_WaterColor);
   		m_WaterSurface->Render();
   
   		for(unsigned int i = 0; i < m_AffectedMeshes.size(); i++)
   		{
   			m_CausticsEffect->PassParameters(m_AffectedMeshes[i]->GetModelMatrix(), m_ViewMatrix, m_ProjectionMatrix, m_CamPos, m_SunLight, m_Ambient, m_WaterColor, m_WaterSurface->GetHeight()); 
   			m_AffectedMeshes[i]->Render();
   		}
  	}
  
  	for(unsigned int i = 0; i < PARTICLESYSTEMS; i++)
  	{
   		m_ParticleSystem[i]->Render(m_ProjectionMatrix, m_ViewMatrix);
  	}
   
   	for(int i = 0; i < SHAFTS; i++)
   	{
   		glDepthMask(GL_FALSE);
   		m_Shaft[i]->PassParameters(m_ProjectionMatrix, m_ViewMatrix);
   		m_Shaft[i]->Render();
   		glDepthMask(GL_TRUE);
   	}
 
 	m_RenderTarget->Deactivate();
}

void Scene::FinalizeScene()
{
	// flag for when the camera gets under water
 	int underwater = 0;
 	if(m_CamPos.y < m_WaterSurface->GetHeight())
 	{
 		underwater = 1;
 	}
 
	// Bind the Depth of Field shader and pass its parameters
 	m_DoFShader->Bind();
 
 	glActiveTexture(GL_TEXTURE0);
 	m_RenderTarget->BindTexture(0);
 
 	glActiveTexture(GL_TEXTURE1);
 	m_RenderTarget->BindDepthBuffer();
 
 	m_DoFShader->SetUniform1i("RenderTarget", 0);
 	m_DoFShader->SetUniform1i("DepthTexture", 1);
 
 	m_DoFShader->SetUniform1f("MinRange", -100);
 	m_DoFShader->SetUniform1f("MaxRange", 100);
 	m_DoFShader->SetUniform1f("BlurSize", 3);
 	m_DoFShader->SetUniform2fv("Samples", DOFSAMPLES, glm::value_ptr(m_Samples[0]));
 	m_DoFShader->SetUniform1i("UnderWater", underwater);
 
	// Render everything to the texture.
 	RenderToTexture();
 	m_DoFShader->Unbind();
}

void Scene::AddAffectedMesh( Liqua::Mesh* a_Mesh )
{
 	a_Mesh->SetShader(m_CausticsEffect->GetShader());
 	m_AffectedMeshes.push_back(a_Mesh);
}

void Scene::PassParameters(const glm::mat4 &a_Projection, const glm::mat4 &a_View , const glm::vec3 &a_CamPos)
{
 	m_ProjectionMatrix = a_Projection;
 	m_ViewMatrix = a_View;
 	m_CamPos = a_CamPos;
}

void Scene::RenderToTexture()
{
 	glDisable(GL_DEPTH_TEST);
 	glDepthMask(TRUE);
 	glEnableVertexAttribArray(0); // 0 for vertex positions
 	glBindBuffer(GL_ARRAY_BUFFER, m_QuadBuffer);
 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
 
 	glDrawArrays(GL_TRIANGLES, 0, 6);
 	glDisableVertexAttribArray(0);
 	glEnable(GL_DEPTH_TEST);
}