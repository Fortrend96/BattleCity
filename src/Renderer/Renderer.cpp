#include "Renderer.h"

namespace RenderEngine 
{
	void CRenderer::draw(const CVertexArray& vertexArray, 
						const CIndexBuffer& indexBuffer,
						const CShaderProgram& shaderProgram)
	{
		shaderProgram.use();
		vertexArray.bind();
		indexBuffer.bind();

		glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void CRenderer::setClearColor(float fRed, float fGreen, float fBlue, float fAlpha)
	{
		glClearColor(fRed, fGreen, fBlue, fAlpha);
	}

	void CRenderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void CRenderer::setViewport(unsigned int iWidth, unsigned int iHeight, unsigned int iLeftOffset, unsigned int iBottomOffset)
	{
		glViewport(iLeftOffset, iBottomOffset, iWidth, iHeight);
	}

	std::string CRenderer::getRendererString() 
	{
		return (char*)glGetString(GL_RENDERER);
	}

	std::string CRenderer::getVersionString() 
	{
		return (char*)glGetString(GL_VERSION);
	}
}
