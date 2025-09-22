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

		void update(const double delta);


	private:
		std::shared_ptr<CSprite> m_pSprite;
		size_t m_currentFrame;
		double m_currentFrameDuration;
		double m_currentAnimationTime;

	};
}
