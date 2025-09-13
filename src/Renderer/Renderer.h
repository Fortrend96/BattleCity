#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

#include <string>

namespace RenderEngine
{
	class CRenderer
	{
	public:
		static void draw(const CVertexArray& vertexArray, const CIndexBuffer& indexBuffer,
			const CShaderProgram& shaderProgram);

		static void setClearColor(float fRed, float fGreen, float fBlue, float fAlpha);

		static void clear();

		static void setViewport(unsigned int iWidth, unsigned int iHeight, 
								unsigned int iLeftOffset = 0, unsigned int iBottomOffset = 0);

		static std::string getRendererString();
		static std::string getVersionString();

	};
}
