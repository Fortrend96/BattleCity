#include "IndexBuffer.h"

namespace RenderEngine
{
	CIndexBuffer::CIndexBuffer():
		m_id(0), m_iCount(0)
	{
	}

	CIndexBuffer::~CIndexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	CIndexBuffer::CIndexBuffer(CIndexBuffer&& indexBuffer) noexcept
	{
		m_id = indexBuffer.m_id;
		indexBuffer.m_id = 0;

		m_iCount = indexBuffer.m_iCount;
		indexBuffer.m_iCount = 0;
	}

	CIndexBuffer& CIndexBuffer::operator=(CIndexBuffer&& indexBuffer) noexcept
	{
		m_id = indexBuffer.m_id;
		indexBuffer.m_id = 0;

		m_iCount = indexBuffer.m_iCount;
		indexBuffer.m_iCount = 0;

		return *this;
	}

	void CIndexBuffer::init(const void* pData, const unsigned int iCount)
	{
		m_iCount = iCount;
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iCount * sizeof(GLuint), pData, GL_STATIC_DRAW);
	}

	void CIndexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void CIndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
