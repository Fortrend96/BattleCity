#pragma once
#include <vector>
#include <glad/glad.h>

namespace Renderer
{
	struct CVertexBufferLayoutElement {
		GLint iCount;
		GLenum eType;
		GLboolean bNormalized;
		unsigned int iSize;
	};

	class CVertexBufferLayout
	{
	public:
		CVertexBufferLayout();

		void reserveElements(const size_t iCount);
		void addElementLayoutFloat(const unsigned int iCount, const bool bNormalized);

		unsigned int getStride() const {return m_iStride;}
		

		const std::vector<CVertexBufferLayoutElement>& getLayoutElements() const {
			return m_layoutElements;				
		}
	private:
		std::vector<CVertexBufferLayoutElement> m_layoutElements;
		unsigned int m_iStride;
	};
}
