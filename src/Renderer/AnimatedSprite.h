#pragma once

#include "Sprite.h"
#include <map>
#include <vector>


namespace RenderEngine
{
	class CAnimatedSprite : public CSprite
	{
	public:
		CAnimatedSprite(std::shared_ptr<CTexture2D> pTexture,
						std::string strInitialSubTexture,
						std::shared_ptr<CShaderProgram> pShaderProgram,
						glm::vec2& position = glm::vec2(0.f),
						glm::vec2& size = glm::vec2(1.f),
						const float rotation = 0.f);

		void insertState(std::string strState,
			std::vector<std::pair<std::string, uint64_t>> subTextureTexturesDuration);

		void render() const override;

		void setState(const std::string& strNewState);

		void update(const uint64_t delta);

	private:
		std::map < std::string, std::vector<std::pair<std::string, size_t>>> m_statesMap;
		size_t m_currentFrame = 0;
		uint64_t m_currentAnimationTime = 0;

		std::map < std::string, std::vector<std::pair<std::string, size_t>>>::const_iterator m_pCurrentAnimationDuration;
		mutable bool m_dirty = false;

	};
}

