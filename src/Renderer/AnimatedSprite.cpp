#include "AnimatedSprite.h"
#include <iostream>
#include "Texture2D.h"

namespace Renderer
{
	CAnimatedSprite::CAnimatedSprite(std::shared_ptr<CTexture2D> pTexture,
									std::string strInitialSubTexture,
									std::shared_ptr<CShaderProgram> pShaderProgram,
									glm::vec2& position,
									glm::vec2& size,
									const float rotation)
		: CSprite(std::move(pTexture), 
			std::move(strInitialSubTexture), 
			std::move(pShaderProgram), 
			position, size, rotation)
	{ 
		m_pCurrentAnimationDuration = m_statesMap.end();
	}
	//--------------------------------------------------------------------------------------------
	void CAnimatedSprite::insertState(std::string strState,
		std::vector<std::pair<std::string, uint64_t>> subTextureTexturesDuration)
	{
		m_statesMap.emplace(std::move(strState), std::move(subTextureTexturesDuration));
	}
	//--------------------------------------------------------------------------------------------
	void CAnimatedSprite::render() const
	{
		if (m_dirty)
		{
			auto subTexture = m_pTexture->getSubTexture(m_pCurrentAnimationDuration->second[m_currentFrame].first);

			const GLfloat textureCoords[] = {
				// U  V
				subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
				subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
			};

			m_textureCoordsBuffer.update(textureCoords, 2 * 4 * sizeof(GLfloat));
			m_dirty = false;
		}

		CSprite::render();
	}
	//--------------------------------------------------------------------------------------------
	void CAnimatedSprite::setState(const std::string& strNewState)
	{
		auto it = m_statesMap.find(strNewState);

		if (it == m_statesMap.end())
		{
			std::cout << "Cant find animated state: " << strNewState << std::endl;
			return;
		}

		if (it != m_pCurrentAnimationDuration)
		{
			m_currentAnimationTime = 0;
			m_currentFrame = 0;
			m_pCurrentAnimationDuration = it;
			m_dirty = true;
		}		
	}
	//--------------------------------------------------------------------------------------------
	void CAnimatedSprite::update(const uint64_t delta)
	{
		if (m_pCurrentAnimationDuration != m_statesMap.end())
		{
			m_currentAnimationTime += delta;

			while (m_currentAnimationTime >= m_pCurrentAnimationDuration->second[m_currentFrame].second)
			{
				m_currentAnimationTime -= m_pCurrentAnimationDuration->second[m_currentFrame].second;
				++m_currentFrame;
				m_dirty = true;

				if (m_currentFrame == m_pCurrentAnimationDuration->second.size())
				{
					m_currentFrame = 0;
				}

			}


		}
	}
	//--------------------------------------------------------------------------------------------
}