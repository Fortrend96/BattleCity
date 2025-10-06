#include "VertexBufferLayout.h"

namespace RenderEngine
{
	VertexBufferLayout::VertexBufferLayout():
		m_iStride(0)
	{

	}

	void VertexBufferLayout::reserveElements(const size_t iCount)
	{
		m_layoutElements.reserve(iCount);
	}

	void VertexBufferLayout::addElementLayoutFloat(const unsigned int iCount, 
													const bool bNormalized)
	{
		
		m_layoutElements.push_back({ static_cast<GLint>(iCount), GL_FLOAT, bNormalized, iCount * static_cast<unsigned int>(sizeof(GLfloat)) });
		m_iStride += m_layoutElements.back().iSize;
	}
}
