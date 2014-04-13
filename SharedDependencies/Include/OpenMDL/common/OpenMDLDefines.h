/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_DEFINES_H_
#define _OPENMDL_COMMON_DEFINES_H_

// compiler configuration

#ifdef _MSC_VER
#	define OPENMDL_VISUALSTUDIO
#	define OPENMDL_COMPILER					"MSVC"
#	define OPENMDL_FUNCTION					__FUNCTION__
#	define OPENMDL_FILE						__FILE__
#	define OPENMDL_LINE						__LINE__
#	define OPENMDL_INLINE					__inline
#	define OPENMDL_LIBEXPORT				__declspec(dllexport)
#	define OPENMDL_LIBIMPORT				__declspec(dllimport)

#	pragma warning(disable : 4275)
#	pragma warning(disable : 4996)
#	pragma warning(disable : 4251)
#	pragma warning(disable : 4482)

#	ifdef _WIN32
#		define OPENMDL_ENV32
#	endif

#	ifdef _WIN64
#		define OPENMDL_ENV64
#	endif
#endif

#ifdef __GNUC__
#	define OPENMDL_GCC
#	define OPENMDL_COMPILER					"GCC"
#	define OPENMDL_FUNCTION					__func__
#	define OPENMDL_FILE						__FILE__
#	define OPENMDL_LINE						__LINE__
#	define OPENMDL_INLINE					inline

#	if __x86_64__ || __ppc64__
#		define OPENMDL_ENV64
#	else
#		define OPENMDL_ENV32
#	endif
#endif



// libexp define

#ifdef OPENMDL_LIBEXP
#	define OPENMDL_EXPORT_FUNCTION			OPENMDL_LIBEXPORT
#else
#	define OPENMDL_EXPORT_FUNCTION			OPENMDL_LIBIMPORT
#endif



// platform configuration

#ifdef _WIN32
#	define OPENMDL_WINDOWS
#endif

#ifdef _WIN64
#	define OPENMDL_WINDOWS
#endif

#ifdef __APPLE__
#	define OPENMDL_OSX
#endif

#ifdef __linux__
#	define OPENMDL_LINUX
#endif



// common helper defines and OpenMDL-specific defines

#define OPENMDL_ALIGNEDMALLOC(x)		_aligned_malloc(x, 64)
#define OPENMDL_ALIGNEDFREE(x)			_aligned_free(x)
#define OPENMDL_SAFE_DELETE(x)			{ if(x) delete x; x = NULL; }
#define OPENMDL_SAFE_ARR_DELETE(x)		{ if(x) delete [] x; x = NULL; }
#define OPENMDL_SAFE_RELEASE(x)			{ if(x) x->Release(); }
#define OPENMDL_SAFE_RELEASE_DELETE(x)	{ if(x) x->Release(); delete x; x = NULL; }
#define OPENMDL_SAFE_FCLOSE(x)			{ if(x) fclose(x); x = NULL; }
#define OPENMDL_SAFE_FREE(x)			{ if(x) free(x); }
#define OPENMDL_BOOL_TO_BYTE(b)			((b) ? 0xFF : 0x00)
#define OPENMDL_BYTE_TO_BOOL(b)			((b) ? true : false)
#define OPENMDL_VERSION_STRING			"0.961 beta"
#define OPENMDL_VERSION_INTEGER			961
#define OPENMDL_VERSION_DOUBLE			0.961
#define OPENMDL_VERSION_FLOAT			0.961f
#define OPENMDL_SCENE_HEADER_ID			0x304c444d6e65704f // Scene file header ID: "OpenMDL0"
#define OPENMDL_ANIMATION_HEADER_ID		0x334c444d6e65704f // Animation file header ID: "OpenMDL3"
#define OPENMDL_STRLEN					128
#define OPENMDL_MAX_TEXCOORDSETS		32
#define OPENMDL_LERP(a, b, t)			(a + t * (b - a))
#define OPENMDL_BIT(b)					(1 << b)

#endif