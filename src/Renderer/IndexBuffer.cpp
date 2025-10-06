#include "IndexBuffer.h"

namespace RenderEngine
{
	IndexBuffer::IndexBuffer():
		m_id(0), m_iCount(0)
	{
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept
	{
		m_id = indexBuffer.m_id;
		indexBuffer.m_id = 0;

		m_iCount = indexBuffer.m_iCount;
		indexBuffer.m_iCount = 0;
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& indexBuffer) noexcept
	{
		m_id = indexBuffer.m_id;
		indexBuffer.m_id = 0;

		m_iCount = indexBuffer.m_iCount;
		indexBuffer.m_iCount = 0;

		return *this;
	}

	void IndexBuffer::init(const void* pData, const unsigned int iCount)
	{
		m_iCount = iCount;
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iCount * sizeof(GLuint), pData, GL_STATIC_DRAW);
	}

	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
