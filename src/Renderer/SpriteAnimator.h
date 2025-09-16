#pragma once

#include <memory>

namespace RenderEngine
{
	class CSprite;

	class CSpriteAnimator 
	{
	public:
		CSpriteAnimator(std::shared_ptr<CSprite> pSprite);
		
		size_t getCurrentFrame() const { return m_currentFrame;	}

		void update(const uint64_t delta);


	private:
		std::shared_ptr<CSprite> m_pSprite;
		size_t m_currentFrame;
		uint64_t m_currentFrameDuration;
		uint64_t m_currentAnimationTime;

	};
}
