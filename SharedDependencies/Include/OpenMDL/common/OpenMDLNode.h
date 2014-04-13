/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_NODE_H_
#define _OPENMDL_COMMON_NODE_H_

#include "OpenMDLCommon.h"

namespace OpenMDL
{
	class OPENMDL_EXPORT_FUNCTION Node
	{
		friend class Importer;
		friend class MayaCommon;
	public:
		Node();
		Node(const char* name, const matrix4x4& transform);
		virtual ~Node();

		matrix4x4&			GetTransform();
		String&				GetName();
		const char*			GetNameCString() const;
		Node*				GetParent() const;
		unsigned int		GetChildCount() const;
		Node*				GetChild(unsigned int index) const;
		Node*				GetChild(const char* name) const;
		NodeType			GetType() const;
		unsigned int		GetAttributeCount() const;
		Attribute*			GetAttribute(const char* name) const;
		Attribute*			GetAttribute(unsigned int index) const;
		unsigned short		GetNameIndex() const;

		void				AddAttribute(const char* name, AttributeType type, void* data, unsigned int length);
		void				AddChild(Node* child);

	protected:
		matrix4x4			m_Transform;
		String				m_Name;
		Node*				m_Parent;
		NodeList			m_Children;
		NodeType			m_Type;
		AttributeList		m_Attributes;
		unsigned short		m_NameIndex;
	};
}

#endif