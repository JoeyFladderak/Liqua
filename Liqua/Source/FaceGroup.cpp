#include "Liqua.h"
#include "FaceGroup.h"

Liqua::FaceGroup::FaceGroup()
{
	m_Vertices.clear();

	m_VertexBuffer = 0;
}

Liqua::FaceGroup::~FaceGroup()
{
	m_Vertices.clear();
}