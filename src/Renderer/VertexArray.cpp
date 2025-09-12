#include "VertexArray.h"

namespace Renderer
{
	CVertexArray::CVertexArray()
	{
		glGenVertexArrays(1, &m_id);
	}

	CVertexArray::~CVertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	CVertexArray::CVertexArray(CVertexArray&& vertexArray) noexcept
	{
		m_id = vertexArray.m_id;
		vertexArray.m_id = 0;
	}

	CVertexArray& CVertexArray::operator=(CVertexArray&& vertexArray) noexcept
	{
		m_id = vertexArray.m_id;
		vertexArray.m_id = 0;
		return *this;
	}

	void CVertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}

	void CVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void CVertexArray::addBuffer(const CVertexBuffer& vertexBuffer, const CVertexBufferLayout& layout)
	{
		bind();
		vertexBuffer.bind();
		const auto& layoutElements = layout.getLayoutElements();
		GLbyte* offset = nullptr;
		for (unsigned int i = 0; i < layoutElements.size(); ++i)
		{
			const auto& currentLayoutElement = layoutElements[i];
			GLuint currentAttribIndex = m_iElementsCount + i;
			glEnableVertexAttribArray(currentAttribIndex);
			glVertexAttribPointer(currentAttribIndex, currentLayoutElement.iCount, currentLayoutElement.eType, 
									currentLayoutElement.bNormalized, layout.getStride(), offset);
			offset += currentLayoutElement.iSize;
		}
		m_iElementsCount += static_cast<unsigned int>(layoutElements.size());
	}
}
