#include "Renderer.h"

namespace RenderEngine 
{
	void Renderer::draw(const VertexArray& vertexArray, 
						const IndexBuffer& indexBuffer,
						const ShaderProgram& shaderProgram)
	{
		shaderProgram.use();
		vertexArray.bind();
		indexBuffer.bind();

		glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::setClearColor(float fRed, float fGreen, float fBlue, float fAlpha)
	{
		glClearColor(fRed, fGreen, fBlue, fAlpha);
	}

	void Renderer::setDepthTest(const bool bEnable)
	{
		if (bEnable)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}

	void Renderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::setViewport(unsigned int iWidth, unsigned int iHeight, unsigned int iLeftOffset, unsigned int iBottomOffset)
	{
		glViewport(iLeftOffset, iBottomOffset, iWidth, iHeight);
	}

	std::string Renderer::getRendererStr()
	{
		return (char*)glGetString(GL_RENDERER);
	}

	std::string Renderer::getVersionStr()
	{
		return (char*)glGetString(GL_VERSION);
	}
}
