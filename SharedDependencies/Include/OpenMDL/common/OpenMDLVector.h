/************************************************************************
	Name:		OpenMDL 
	Version:	0.96.1 beta
	Date:		May 10, 2013
	Author:		Eric H. den Boer
	Contact:	http://www.openmdl.org
	License:	Creative Commons Attribution 3.0 Unported (http://www.openmdl.org/license/)
*************************************************************************/
#ifndef _OPENMDL_COMMON_VECTOR_H_
#define _OPENMDL_COMMON_VECTOR_H_

#define OPENMDL_VECTOR_SIZE 4

namespace OpenMDL
{
	template <class _Type>
	class Vector
	{
	public:
		Vector();
		Vector(const Vector<_Type>& copy);
		~Vector();
		
		void					Push(const _Type& item);
		void					Pop();
		unsigned int			Size() const { return (unsigned int)m_Top + 1; }
		void					Clear(bool deallocate = false);
		void					Erase(int index);
		void					Deallocate();
		void					Allocate(int elements);
		unsigned int			Capacity() const { return (unsigned int)m_BufferSize; }
		const _Type*			GetBuffer() const { return m_Buffer; }

		const _Type& operator	[] (int index) const { return m_Buffer[index]; }
		_Type& operator			[] (int index) { return m_Buffer[index]; }
		void operator			= (const Vector<_Type>& copy);

	protected:
		int						m_Top;
		_Type*					m_Buffer;
		int						m_BufferSize;
	};


	//////////////////////////////////////////////////////////////////////////
	// Vector<_Type> implementations
	//////////////////////////////////////////////////////////////////////////

	template <class _Type>
	OpenMDL::Vector<_Type>::Vector()
	{
		m_Top = -1;
		m_Buffer = new _Type[OPENMDL_VECTOR_SIZE];
		m_BufferSize = OPENMDL_VECTOR_SIZE;
	}

	template <class _Type>
	OpenMDL::Vector<_Type>::Vector(const Vector<_Type>& copy)
	{
		m_Top = copy.m_Top;
		m_Buffer = new _Type[copy.m_BufferSize];
		m_BufferSize = copy.m_BufferSize;
		memcpy(m_Buffer, copy.m_Buffer, sizeof(_Type) * m_BufferSize);
	}

	template <class _Type>
	OpenMDL::Vector<_Type>::~Vector()
	{
		OPENMDL_SAFE_ARR_DELETE(m_Buffer);
	}

	template <class _Type>
	void OpenMDL::Vector<_Type>::Push(const _Type& item)
	{
		if((m_Top + 1) >= m_BufferSize)
		{
			const int newBufferSize = m_BufferSize + (m_BufferSize >> 1);

			// allocate new buffer
			_Type* tempbuffer = new _Type[newBufferSize];
			memcpy(tempbuffer, m_Buffer, sizeof(_Type) * m_BufferSize);

			// delete old buffer and reference the new data and size
			OPENMDL_SAFE_ARR_DELETE(m_Buffer);
			m_Buffer = tempbuffer;
			m_BufferSize = newBufferSize;
		}

		++m_Top;
		m_Buffer[m_Top] = item;
	}

	template <class _Type>
	void OpenMDL::Vector<_Type>::Pop()
	{
		if(m_Top < 0) 
			return;

		--m_Top;
	}

	template <class _Type>
	void OpenMDL::Vector<_Type>::operator=(const Vector<_Type>& copy)
	{
		OPENMDL_SAFE_ARR_DELETE(m_Buffer);

		m_Top = copy.m_Top;
		m_Buffer = new _Type[copy.m_BufferSize];
		m_BufferSize = copy.m_BufferSize;
		memcpy(m_Buffer, copy.m_Buffer, sizeof(_Type) * m_BufferSize);
	}

	template <class _Type>
	void OpenMDL::Vector<_Type>::Clear(bool deallocate /* = false */)
	{
		if(deallocate)
		{
			OPENMDL_SAFE_ARR_DELETE(m_Buffer);
			m_Buffer = new _Type[OPENMDL_VECTOR_SIZE];
			m_BufferSize = OPENMDL_VECTOR_SIZE;
		}

		m_Top = -1;
	}

	template <class _Type>
	void OpenMDL::Vector<_Type>::Erase(int index)
	{
		if(index >= 0 && index < m_Top)
		{		
			memcpy(&m_Buffer[index], &m_Buffer[index + 1], sizeof(_Type) * (m_Top - index));
			--m_Top;
		}
	}

	template <class _Type>
	void OpenMDL::Vector<_Type>::Deallocate()
	{
		OPENMDL_SAFE_ARR_DELETE(m_Buffer);
		m_Buffer = new _Type[OPENMDL_VECTOR_SIZE];
		m_BufferSize = OPENMDL_VECTOR_SIZE;
		m_Top = -1;
	}

	template <class _Type>
	void OpenMDL::Vector<_Type>::Allocate(int elements)
	{
		OPENMDL_SAFE_ARR_DELETE(m_Buffer);
		m_Buffer = new _Type[elements];
		m_BufferSize = elements;
		m_Top = -1;
	}
}

#endif