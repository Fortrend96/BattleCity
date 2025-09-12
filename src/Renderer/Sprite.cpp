#include "Sprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Renderer {
    CSprite::CSprite( std::shared_ptr<CTexture2D> pTexture,
        std::string strInitialSubTexture,
         std::shared_ptr<CShaderProgram> pShaderProgram,
        glm::vec2& position,
        glm::vec2& size,
        const float fRotation)
        : m_pTexture(std::move(pTexture))
        , m_pShaderProgram(std::move(pShaderProgram))
        , m_position(position)
        , m_size(size)
        , m_fRotation(fRotation)
    {
        const GLfloat vertexCoords[] = {
            // 1---2
            // | / | 
            // 0---3

            // X  Y
            0.f, 0.f,
            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f,
        };

        auto subTexture = m_pTexture->getSubTexture(std::move(strInitialSubTexture));

        const GLfloat textureCoords[] = {
            // U  V

            subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
            subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
            subTexture.rightTopUV.x, subTexture.rightTopUV.y,
            subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
        };

        const GLuint indices[] = {
            0,1,2,
            2,3,0
        };

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_vertexCoordsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glGenBuffers(1, &m_textureCoordsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), &textureCoords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

	CSprite::~CSprite() 
	{
		glDeleteBuffers(1, &m_vertexCoordsVBO);
		glDeleteBuffers(1, &m_textureCoordsVBO);
        glDeleteBuffers(1, &m_EBO);

		glDeleteVertexArrays(1, &m_VAO);
	}


	void CSprite::render() const 
	{
        m_pShaderProgram->use();

        glm::mat4 model(1.f);

        model = glm::translate(model, glm::vec3(m_position, 0.f));
        model = glm::translate(model, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.f));
        model = glm::rotate(model, glm::radians(m_fRotation), glm::vec3(0.f, 0.f, 1.f));
        model = glm::translate(model, glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0.f));
        model = glm::scale(model, glm::vec3(m_size, 1.f));

        glBindVertexArray(m_VAO);
        m_pShaderProgram->setMatrix4("modelMat", model);

        glActiveTexture(GL_TEXTURE0);
        m_pTexture->bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
	}

	void CSprite::setPosition(const glm::vec2& position)
	{
		m_position = position;
	}

	void CSprite::setSize(const glm::vec2& size) 
	{
		m_size = size;
	}

	void CSprite::setRotation(const float fRotation) 
	{
		m_fRotation = fRotation;
	}
}
