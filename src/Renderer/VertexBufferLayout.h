#pragma once
#include <vector>
#include <glad/glad.h>

namespace RenderEngine
{
	struct VertexBufferLayoutElement {
		GLint iCount;
		GLenum eType;
		GLboolean bNormalized;
		unsigned int iSize;
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout();

		void reserveElements(const size_t iCount);
		void addElementLayoutFloat(const unsigned int iCount, const bool bNormalized);

		unsigned int getStride() const {return m_iStride;}
		

		const std::vector<VertexBufferLayoutElement>& getLayoutElements() const {
			return m_layoutElements;				
		}
	private:
		std::vector<VertexBufferLayoutElement> m_layoutElements;
		unsigned int m_iStride;
	};
}
