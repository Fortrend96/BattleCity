#include "Sprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"

#include "Renderer.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace RenderEngine {
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

        m_vertexCoordsBuffer.init(vertexCoords, 2 * 4 * sizeof(GLfloat));
        CVertexBufferLayout vertexCoordsLayout;
        vertexCoordsLayout.addElementLayoutFloat(2, false);
        m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLayout);

        m_textureCoordsBuffer.init(textureCoords, 2 * 4 * sizeof(GLfloat));
        CVertexBufferLayout textureCoordsLayout;
        textureCoordsLayout.addElementLayoutFloat(2, false);
        m_vertexArray.addBuffer(m_textureCoordsBuffer, textureCoordsLayout);

        m_indexBuffer.init(indices, 6);

        m_vertexArray.unbind();
        m_indexBuffer.unbind();
    }

	CSprite::~CSprite() 
	{
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

        m_pShaderProgram->setMatrix4("modelMat", model);

        glActiveTexture(GL_TEXTURE0);
        m_pTexture->bind();

        CRenderer::draw(m_vertexArray, m_indexBuffer, *m_pShaderProgram);
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
