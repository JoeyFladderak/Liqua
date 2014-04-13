/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_ANIMATION_H_
#define _OPENMDL_COMMON_ANIMATION_H_

namespace OpenMDL
{
	class AnimationFrame;

	class OPENMDL_EXPORT_FUNCTION Animation
	{
		friend class Importer;
		friend class MayaCommon;
		friend class MayaExporter;
		friend class Options;
	public:
		Animation();
		Animation(const char* name, unsigned int startframe, unsigned int endframe, float fps);
		~Animation();

		unsigned int		GetFrameCount() const;
		AnimationFrame*		GetFrame(unsigned int index) const;
		String&				GetName();
		float				GetFps() const;
		unsigned int		GetStartFrame() const;
		unsigned int		GetEndFrame() const;

	protected:
		FrameList			m_Frames;
		String				m_Name;
		float				m_Fps;
		unsigned int		m_StartFrame;
		unsigned int		m_EndFrame;
	};
}

#endif