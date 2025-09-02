#pragma once

#include <glad/glad.h>
#include <memory>
#include <string>
#include <glm/vec2.hpp>

namespace Renderer
{
	class CTexture2D;
	class CShaderProgram;


	class CSprite
	{
	public:
		CSprite(const std::shared_ptr<CTexture2D> pTexture,
			std::string strInitialSubTexture,
			const std::shared_ptr<CShaderProgram> pShaderProgram,
			glm::vec2& position = glm::vec2(0.f),
			glm::vec2& size = glm::vec2(1.f),
			const float rotation = 0.f);

		~CSprite();

		CSprite(const CSprite&) = delete;
		CSprite& operator=(const CSprite&) = delete;

		void render() const;

		void setPosition(const glm::vec2& position);

		void setSize(const glm::vec2& size);

		void setRotation(const float fRotation);

	private:
		std::shared_ptr<CTexture2D> m_pTexture;
		std::shared_ptr<CShaderProgram> m_pShaderProgram;
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_fRotation;

		GLuint m_VAO; // vertex array object
		GLuint m_vertexCoordsVBO;
		GLuint m_textureCoordsVBO;
	};
}
