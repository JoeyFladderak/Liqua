/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_MAYA_OPTIONS_H_
#define _OPENMDL_MAYA_OPTIONS_H_

// Hacky file is hacky, I know...

#ifdef OPENMDL_MAX
// stuff
#endif
#ifdef OPENMDL_MAYA
#	include <maya/MString.h>
#	include <maya/MStringArray.h>
#endif

namespace OpenMDL
{
	class OPENMDL_EXPORT_FUNCTION Options
	{
	public:
#ifdef OPENMDL_MAX
		static void			Parse(...);
#endif
#ifdef OPENMDL_MAYA
		static void			Parse(const MString& optionstring);
#endif

		static bool			doGeometry;
		static bool			doMaterials;
		static bool			doTangents;
		static bool			doNormals;
		static bool			doTexCoords;
		static bool			doJoints;
		static bool			doAnimations;
		static bool			doTriangulate;
		static bool			doAxis;
		static bool			doExportSelected;
		static bool			invertU;
		static bool			invertV;
		static String		animFile;
	};
}
#endif