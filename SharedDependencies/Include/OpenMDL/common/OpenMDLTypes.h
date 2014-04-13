/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_TYPES_H_
#define _OPENMDL_COMMON_TYPES_H_

namespace OpenMDL
{
	class Node;
	class Material;
	class Weight;
	class Mesh;
	class Joint;
	class JointPose;
	class Animation;
	class AnimationFrame;
	class Skeleton;
	class Transform;
	class TransformPose;
	class Attribute;
	class Scene;
	class FaceGroup;

	struct OPENMDL_EXPORT_FUNCTION float2
	{
		float2() { x = 0; y = 0; }
		float2(float _x, float _y) { x = _x; y = _y; }
		
		union
		{
			float cell[2];
			struct
			{
				float x;
				float y;
			};

			struct  
			{
				float u;
				float v;
			};
		};
	};

	struct OPENMDL_EXPORT_FUNCTION float3
	{
		float3() { x = 0; y = 0; z = 0; }
		float3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }

		union
		{
			float cell[3];
			struct
			{
				float x;
				float y;
				float z;
			};
		};
	};

	struct OPENMDL_EXPORT_FUNCTION float4
	{
		float4() { x = 0; y = 0; z = 0; w = 0; }
		float4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }

		union
		{
			float cell[4];
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
		};
	};

	struct OPENMDL_EXPORT_FUNCTION matrix3x3
	{
		matrix3x3() 
		{ 
			c11 = 1; c12 = 0; c13 = 0;
			c21 = 0; c22 = 1; c23 = 0;
			c31 = 0; c32 = 0; c33 = 1;
		}

		union
		{
			float cell[9];
			float c[3][3];
			struct  
			{
				float	c11, c12, c13,
						c21, c22, c23,
						c31, c32, c33;
			};
		};
	};

	struct OPENMDL_EXPORT_FUNCTION matrix4x4
	{
		matrix4x4() 
		{ 
			c11 = 1; c12 = 0; c13 = 0; c14 = 0;
			c21 = 0; c22 = 1; c23 = 0; c24 = 0;
			c31 = 0; c32 = 0; c33 = 1; c34 = 0;
			c41 = 0; c42 = 0; c43 = 0; c44 = 1;
		}

		union
		{
			float cell[16];
			float c[4][4];
			struct  
			{
				float	c11, c12, c13, c14,
						c21, c22, c23, c24,
						c31, c32, c33, c34,
						c41, c42, c43, c44;
			};
		};
	};

	struct OPENMDL_EXPORT_FUNCTION colorf
	{
		colorf() { r = 0; g = 0; b = 0; a = 1; }
		colorf(float _r, float _g, float _b, float _a) { r = _r; g = _g; b = _b; a = _a; }

		bool IsBlack() { return !((r + g + b) > 0); }

		union
		{
			float cell[4];
			struct
			{
				float r;
				float g;
				float b;
				float a;
			};
		};
	};

	enum NodeType
	{
		eNodeType_Transform		= 1,
		eNodeType_Mesh			= 2,
		eNodeType_Joint			= 3,
	};

	enum AttributeType
	{
		eAttributeType_Int		= 1,
		eAttributeType_Float	= 2,
		eAttributeType_String	= 3,
		eAttributeType_Float3	= 4
	};

	enum LoadFlag
	{
		eLoadFlag_All			= 0,
		eLoadFlag_NoMaterials	= OPENMDL_BIT(0),
		eLoadFlag_NoUVs			= OPENMDL_BIT(1),
		eLoadFlag_NoJoints		= OPENMDL_BIT(2),
		eLoadFlag_NoTangents	= OPENMDL_BIT(3),
		eLoadFlag_NoNormals		= OPENMDL_BIT(4),
		eLoadFlag_NoAnimations	= OPENMDL_BIT(5)
	};

	typedef OpenMDL::Vector<Node*>							NodeList;
	typedef OpenMDL::Vector<Material*>						MaterialList;
	typedef OpenMDL::Vector<Mesh*>							MeshList;
	typedef OpenMDL::Vector<Joint*>							JointList;
	typedef OpenMDL::Vector<Animation*>						AnimationList;
	typedef OpenMDL::Vector<Skeleton*>						SkeletonList;
	typedef OpenMDL::Vector<Weight*>						WeightList;
	typedef OpenMDL::Vector<Transform*>						TransformList;
	typedef OpenMDL::Vector<Attribute*>						AttributeList;
	typedef OpenMDL::Vector<float2>							Float2List;
	typedef OpenMDL::Vector<float3>							Float3List;
	typedef OpenMDL::Vector<float4>							Float4List;
	typedef OpenMDL::Vector<Float2List>						UVSetList;
	typedef OpenMDL::Vector<int>							IntList;
	typedef OpenMDL::Vector<unsigned int>					UIntList;
	typedef OpenMDL::Vector<OpenMDL::Vector<unsigned int>>	UVIndexSetList;
	typedef OpenMDL::Vector<String>							StringList;
	typedef OpenMDL::Vector<Scene*>							SceneList;
	typedef OpenMDL::Vector<FaceGroup*>						FaceGroupList;
	typedef OpenMDL::Vector<AnimationFrame*>				FrameList;
	typedef OpenMDL::Vector<JointPose*>						JointPoseList;
	typedef OpenMDL::Vector<TransformPose*>					TransformPoseList;
}

#endif