#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include <glad/glad.h>
#include <memory>
#include <string>
#include <glm/vec2.hpp>

namespace RenderEngine
{
	class CTexture2D;
	class CShaderProgram;


	class CSprite
	{
	public:
		CSprite( std::shared_ptr<CTexture2D> pTexture,
			std::string strInitialSubTexture,
			 std::shared_ptr<CShaderProgram> pShaderProgram);

		~CSprite();

		CSprite(const CSprite&) = delete;
		CSprite& operator=(const CSprite&) = delete;

		virtual void render(const glm::vec2& position, const glm::vec2& size, const float fRotation) const;

	protected:
		std::shared_ptr<CTexture2D> m_pTexture;
		std::shared_ptr<CShaderProgram> m_pShaderProgram;

		CVertexArray m_vertexArray;
		CVertexBuffer m_vertexCoordsBuffer;
		CVertexBuffer m_textureCoordsBuffer;
		CIndexBuffer m_indexBuffer;
	};
}
