/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_IMPORTER_H_
#define _OPENMDL_IMPORTER_H_

#include "../common/OpenMDLCommon.h"

namespace OpenMDL
{
	struct AnimationInstance 
	{
		AnimationInstance()
		{
			animation = NULL;
		}

		OpenMDL::Animation*	animation;
		OpenMDL::String animationFile;
	};
	typedef OpenMDL::Vector<AnimationInstance> AnimInstanceList;

	class Scene;
	class OPENMDL_EXPORT_FUNCTION Importer
	{
	public:
		virtual ~Importer();

		static Importer*		GetSingleton();
		static void				DeleteSingleton();

		OpenMDL::Scene*			LoadScene(const char* filename, const char* animationfile = NULL, unsigned int loadflags = eLoadFlag_All);
		bool					LoadAnimation(const char* filename, const char* animationname = NULL);
		bool					AttachAnimations(OpenMDL::Scene* scene, const char* animationfile = NULL);
		bool					DeleteScene(const char* filename);
		bool					DeleteScene(OpenMDL::Scene* scene);
		SceneList&				GetScenes();
		AnimInstanceList&		GetAnimations();
		Animation*				GetAnimation(const char* name, const char* animationfile = NULL);

	protected:
		Importer();

		bool					readHeader(Scene* scene);
		bool					readNameTable(Scene* scene);
		bool					readMaterialTable(Scene* scene);
		bool					readTransformTable(Scene* scene);
		bool					readMeshTable(Scene* scene);
		bool					readJointTable(Scene* scene);
		OpenMDL::String&		getNameByIndex(unsigned short index);
		OpenMDL::Node*			createNode(NodeType type, const String& name);

		SceneList				m_Scenes;
		AnimInstanceList		m_Animations;

		static Importer*		ms_Singleton;
	};
}

#endif