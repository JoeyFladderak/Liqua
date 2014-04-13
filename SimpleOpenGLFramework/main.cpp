#include "Liqua.h"
#include "Mesh.h"
#include "Shader.h"
#include "Scene.h"
#include "Camera.h"
#include "Timer.h"

Scene* g_Scene;
Camera* g_Camera;

Liqua::Timer g_Timer;
float g_DT = 0.5f;

glm::mat4 g_ProjectionMatrix;
glm::mat4 g_ViewMatrix;

glm::ivec2 g_PreviousMousePosition;
glm::vec3 g_DefaultCameraPosition( 0, 50, 70 );

void InitGLUT( int argc, char** argv );
void InitGLEW();
void InitGL();

// GLUT callbacks
// Invoked when we need to redraw the screen.
void OnDisplay();
// Invoked when there are no inputs to process from the user.
void OnIdle();
// Invoked when the window changes size.
void OnReshape( int width, int height );
// Invoked when the user presses a key on the keyboard.
void OnKeyPressed( unsigned char key, int x, int y );
// Invoked when the user releases the key on the keyboard.
void OnKeyReleased( unsigned char key, int x, int y );
// Invoked when the user presses a special key (non-ascii) on the keyboard.
void OnSpecialKeyPressed( int key, int x, int y );
// Invoked when the user releases a special key (non-ascii) on the keyboard.
void OnSpecialKeyReleased( int key, int x, int y );
// Invoked when the user presses or releases the mouse button on the screen.
void OnMouseButton( int button, int state, int x, int y );
// Invoked when the user scrolls the mouse wheel.
void OnMouseWheel( int button, int state, int x, int y );
// Invoked when the user moves the mouse in the screen while any mouse button is pressed.
void OnMouseMotion( int x, int y );
// Invoked when the user moves the mouse in the screen while no mouse buttons are pressed.
void OnPassiveMouseMotion( int x, int y );
void OnClose();

int main(int argc, char** argv)
{
	srand(time(NULL));

	InitGLUT(argc, argv);
	g_Camera = new Camera(g_DefaultCameraPosition, glm::vec3(0.0f, 0.0f, 1.0f));
	InitGLEW();
	InitGL();

	g_ViewMatrix = g_Camera->GetViewMatrix();

	g_Scene = new Scene();

	glutMainLoop();

	return 0;
}

void InitGLUT( int argc, char** argv )
{
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	//glutInitContextVersion( 4, 0 );
	glutInitWindowSize(SCRWIDTH, SCRHEIGHT);

	int screenWidth = glutGet( GLUT_SCREEN_WIDTH );
	int screenHeight = glutGet( GLUT_SCREEN_HEIGHT );

	// Center the new window relative to the screen.
	glutInitWindowPosition( (screenWidth - SCRWIDTH)/2, (screenHeight - SCRHEIGHT)/2 );
	
	glutCreateWindow("Liqua Demo");

	glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS );

	// Register GLUT callbacks
	glutDisplayFunc(&OnDisplay);
	glutIdleFunc(&OnIdle);
	glutReshapeFunc(&OnReshape);
	glutKeyboardFunc(&OnKeyPressed);
	glutKeyboardUpFunc(&OnKeyReleased);
	glutSpecialFunc(&OnSpecialKeyPressed);
	glutSpecialUpFunc(&OnSpecialKeyReleased);
	glutMouseFunc(&OnMouseButton);
	glutMouseWheelFunc(&OnMouseWheel); 
	glutMotionFunc(&OnMouseMotion); 
	glutPassiveMotionFunc(&OnPassiveMouseMotion); 
	glutCloseFunc(&OnClose);

	CheckGL();
}

void InitGLEW()
{
	GLenum res = glewInit();
	if (res != GLEW_OK) 
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return;
	}

	CheckGL();

	if(!GLEW_VERSION_4_0)
	{
		fprintf(stderr, "Error, OpenGL 4.0 required: '%s'\n", glewGetErrorString(res));
		return;
	}

	CheckGL();
}

void InitGL()
{
	// Clear any accumulated OpenGL errors.
	while ( glGetError() != GL_NO_ERROR );

	// Output interesting information about the platform we are using
	std::cout << "Vendor: " << glGetString (GL_VENDOR) << std::endl; CheckGL();
	std::cout << "Renderer: " << glGetString (GL_RENDERER) << std::endl; CheckGL();
	std::cout << "Version: " << glGetString (GL_VERSION) << std::endl; CheckGL();
	std::cout << "GLSL: " << glGetString (GL_SHADING_LANGUAGE_VERSION) << std::endl; CheckGL();

	// Initialize some default OpenGL states
	glClearColor( 0.08f, 0.4f, 1.0f, 1 ); CheckGL();
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OnIdle()
{
	g_Timer.Start();
	
 	g_Scene->UpdateScene(g_DT);
 	g_Scene->RenderScene();
 
 	g_Scene->PassParameters(g_Camera->GetProjectionMatrix(), g_Camera->GetViewMatrix(), g_Camera->GetPosition());

 	g_Scene->FinalizeScene();

	glutWarpPointer(SCRWIDTH / 2, SCRHEIGHT / 2);
	glutSwapBuffers(); CheckGL();

	g_Timer.End();
	g_DT = g_Timer.GetTime();
}

void OnKeyPressed( unsigned char key, int x, int y )
{
	switch (key)
	{
	case 27:    // ESC
		{
			glutLeaveMainLoop(); CheckGL();
		}
		break;
	case 'W':
	case 'w':
		{
			g_Camera->Forward();
		}
		break;
	case 'S':
	case 's':
		{
			g_Camera->BackWard();
		}
		break;
	case 'A':
	case 'a':
		{
			g_Camera->Left();
		}
		break;
	case 'D':
	case 'd':
		{
			g_Camera->Right();
		}
		break;



// 	case 'P':
// 	case 'p':
// 		{
// 			g_Scene->m_LighShaftEffect->m_Exposure += 0.0001;
// 			std::cout << "Exposure: " << g_Scene->m_LighShaftEffect->m_Exposure << std::endl;
// 		}
// 		break;
// 	case 'L':
// 	case 'l':
// 		{
// 			g_Scene->m_LighShaftEffect->m_Exposure -= 0.0001;
// 			std::cout << "Exposure: " << g_Scene->m_LighShaftEffect->m_Exposure << std::endl;
// 		}
// 		break;
// 	case 'O':
// 	case 'o':
// 		{
// 			g_Scene->m_LighShaftEffect->m_Decay += 0.001;
// 			std::cout << "Decay: " << g_Scene->m_LighShaftEffect->m_Decay << std::endl;
// 		}
// 		break;
// 	case 'K':
// 	case 'k':
// 		{
// 			g_Scene->m_LighShaftEffect->m_Decay -= 0.001;
// 			std::cout << "Decay: " << g_Scene->m_LighShaftEffect->m_Decay << std::endl;
// 		}
// 		break;
// 	case 'I':
// 	case 'i':
// 		{
// 			g_Scene->m_LighShaftEffect->m_Density += 0.01;
// 			std::cout << "Density: " << g_Scene->m_LighShaftEffect->m_Density << std::endl;
// 		}
// 		break;
// 	case 'J':
// 	case 'j':
// 		{
// 			g_Scene->m_LighShaftEffect->m_Density -= 0.01;
// 			std::cout << "Density: " << g_Scene->m_LighShaftEffect->m_Density << std::endl;
// 		}
// 		break;
// 	case 'U':
// 	case 'u':
// 		{
// 			g_Scene->m_LighShaftEffect->m_Weight += 0.1;
// 			std::cout << "Weight: " << g_Scene->m_LighShaftEffect->m_Weight << std::endl;
// 		}
// 		break;
// 	case 'H':
// 	case 'h':
// 		{
// 			g_Scene->m_LighShaftEffect->m_Weight -= 0.1;
// 			std::cout << "Weight: " << g_Scene->m_LighShaftEffect->m_Weight << std::endl;
// 		}
// 		break;
	}
}

void OnReshape( int width, int height )
{
	if ( height < 1 ) height = 1;

	// Full-screen view port
	g_Camera->SetViewport( 0, 0, width, height );
	g_Camera->SetProjection( 60.0f, width/(float)height, 0.1f, 5000.0f );
	g_ProjectionMatrix = g_Camera->GetProjectionMatrix();
}

void OnDisplay()
{
	
}

void OnClose()
{
	// clean up
}

void OnKeyReleased( unsigned char key, int x, int y )
{

}

void OnSpecialKeyPressed(int Key, int x, int y)
{
	//g_Camera->OnKeyboard(Key);
// 	switch(Key)
// 	{
// 	case GLUT_KEY_UP:
// 		{
// 			g_Camera->VerticalRotate(1.0f);
// 		}
// 		break;
// 	case GLUT_KEY_DOWN:
// 		{
// 			g_Camera->VerticalRotate(-1.0f);
// 		}
// 		break;
// 	case GLUT_KEY_LEFT:
// 		{
// 			g_Camera->HorizontalRotate(1.0f);
// 		}
// 		break;
// 	case GLUT_KEY_RIGHT:
// 		{
// 			g_Camera->HorizontalRotate(-1.0f);
// 		}
// 		break;
// 	}
}

void OnSpecialKeyReleased( int key, int x, int y )
{

}

void OnMouseButton( int button, int state, int x, int y )
{

}

void OnMouseWheel( int button, int state, int x, int y )
{

}

void OnMouseMotion(int x, int y)
{
	
}

void OnPassiveMouseMotion( int x, int y )
{
	if(g_Camera->IsInitialized())
		g_Camera->OnMouse(x, y);
}