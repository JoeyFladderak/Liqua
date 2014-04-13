#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include "Shlwapi.h"
#include <time.h>

#include "Glew/glew.h"
#include "Freeglut/freeglut.h"
#include "soil/SOIL.h"
#include "OpenMDL/importer/OpenMDL.h"

#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "MathHelper.h"

#ifdef _WINDLL
#define LIQUA_EXPORT_DLL
#else
#define LIQUA_STATIC_LIB
#endif

#ifdef LIQUA_STATIC_LIB
	#define LIQUAEXPORT
	#else
		#ifdef LIQUA_EXPORT_DLL
			#define LIQUAEXPORT __declspec(dllexport) 
		#else
			#define LIQUAEXPORT __declspec(dllimport) 
	#endif
#endif

#define SCRWIDTH 1280
#define SCRHEIGHT 720

// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#   pragma warning (disable : 4251)

inline void CheckOpenGLError( const char* msg, const char* file, int line )
{
	GLenum errorCode = GL_NO_ERROR;
	while ( ( errorCode = glGetError() ) != GL_NO_ERROR )
	{
		std::stringstream ss;
		const GLubyte* errorString = gluErrorString(errorCode);

		if ( errorString != NULL )
		{

			ss << file << "(" << line << "): OpenGL Error: " << errorString << ": " << msg << std::endl;
#ifdef _WIN32
			OutputDebugStringA( ss.str().c_str() );
#else
			std::cerr << ss;
#endif
		}
	}
}

#ifdef _DEBUG
#define CheckGL() CheckOpenGLError( __FUNCSIG__, __FILE__, __LINE__ )
#else
#define CheckGL() ((void*)0) // Do nothing in release builds.
#endif 