/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_MATERIAL_H_
#define _OPENMDL_COMMON_MATERIAL_H_

#include "OpenMDLCommon.h"

namespace OpenMDL
{
	class OPENMDL_EXPORT_FUNCTION Material
	{
		friend class MayaCommon;
		friend class Importer;
	public:
		Material();
		Material(const char* name);
		~Material();

		colorf&					GetAmbientColor();
		colorf&					GetDiffuseColor();
		colorf&					GetEmissiveColor();
		colorf&					GetTransparentColor();
		colorf&					GetReflectiveColor();
		colorf&					GetSpecularColor();
		
		float					GetReflectiveCoeff();
		float					GetTransparentCoeff();
		float					GetSpecularCoeff();
		float					GetGlowCoeff();
		float					GetDiffuseCoeff();

		float					GetRefractionIndex();
		unsigned int			GetRefractionLimit();
		float					GetLightAbsorbance();
		float					GetSurfaceThickness();
		float					GetShadowAttenuation();
		bool					GetChromaticAberration();
		unsigned int			GetReflectionLimit();
		float					GetReflectionSpecularity();
		
		String&					GetAmbientMap();
		String&					GetDisplacementMap();
		String&					GetDiffuseMap();
		String&					GetEmissiveMap();
		String&					GetSpecularMap();
		String&					GetNormalMap();
		String&					GetOpacityMap();
		String&					GetTransparencyMap();
		String&					GetReflectionMap();
		String&					GetGlowMap();
		String&					GetRefractionMap();
		String&					GetLightAbsorbanceMap();
		String&					GetSurfaceThicknessMap();
		String&					GetShadowAttenuationMap();
		String&					GetReflectionSpecularityMap();
		String&					GetShaderFile();
		String&					GetName();

		void					AddAttribute(const char* name, AttributeType type, void* data, unsigned int datasize);
		void					RemoveAttribute(const char* name);
		Attribute*				GetAttribute(const char* name) const;
		unsigned int			GetAttributeCount() const;
		Attribute*				GetAttribute(unsigned int index) const;

	protected:
		colorf					m_AmbientColor;
		colorf					m_DiffuseColor;
		colorf					m_EmissiveColor;
		colorf					m_TransparentColor;
		colorf					m_ReflectiveColor;
		colorf					m_SpecularColor;

		float					m_ReflectiveCoeff;
		float					m_TransparentCoeff;
		float					m_SpecularCoeff;
		float					m_GlowCoeff;
		float					m_DiffuseCoeff;

		float					m_RefractionIndex;
		unsigned int			m_RefractionLimit;
		float					m_LightAbsorbance;
		float					m_SurfaceThickness;
		float					m_ShadowAttenuation;
		bool					m_ChromAberration;
		unsigned int			m_ReflectionLimit;
		float					m_ReflectionSpec;

		String					m_AmbientMap;
		String					m_DisplacementMap;
		String					m_DiffuseMap;
		String					m_EmissiveMap;
		String					m_SpecularMap;
		String					m_NormalMap;
		String					m_OpacityMap;
		String					m_TransparencyMap;
		String					m_ReflectionMap;
		String					m_GlowMap;
		String					m_RefractionMap;
		String					m_LightAbsorbanceMap;
		String					m_SurfaceThicknessMap;
		String					m_ShadowAttenuationMap;
		String					m_ReflectionSpecMap;
		String					m_ShaderFile;
		String					m_Name;

		AttributeList			m_Attributes;
	};
}

#endif