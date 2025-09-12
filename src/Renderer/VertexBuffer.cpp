#include "VertexBuffer.h"

namespace Renderer
{
	CVertexBuffer::CVertexBuffer():
		m_id(0)
	{
	}

	CVertexBuffer::~CVertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	CVertexBuffer::CVertexBuffer(CVertexBuffer&& vertexBuffer) noexcept
	{
		m_id = vertexBuffer.m_id;
		vertexBuffer.m_id = 0;
	}

	CVertexBuffer& CVertexBuffer::operator=(CVertexBuffer&& vertexBuffer) noexcept
	{
		m_id = vertexBuffer.m_id;
		vertexBuffer.m_id = 0;
		return *this;
	}

	void CVertexBuffer::init(const void* pData, const unsigned int size)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, pData, GL_STATIC_DRAW);
	}

	void CVertexBuffer::update(const void* pData, const unsigned int size) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, pData);
	}

	void CVertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void CVertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
