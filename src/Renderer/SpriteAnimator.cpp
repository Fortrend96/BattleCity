#include "SpriteAnimator.h"
#include "Sprite.h"

namespace RenderEngine
{
	CSpriteAnimator::CSpriteAnimator(std::shared_ptr<CSprite> pSprite)
		: m_pSprite(pSprite),
		m_currentFrame(0),
		m_currentFrameDuration(pSprite->getFrameDuration(m_currentFrame)),
		m_currentAnimationTime(0)
	{

	}

	void CSpriteAnimator::update(const uint64_t delta)
	{
		m_currentAnimationTime += delta;

		while (m_currentAnimationTime >= m_currentFrameDuration)
		{
			m_currentAnimationTime -= m_currentFrameDuration;
			++m_currentFrame;

			if (m_currentFrame == m_pSprite->getFramesCount())
			{
				m_currentFrame = 0;
			}
			m_currentFrameDuration = m_pSprite->getFrameDuration(m_currentFrame);
		}
	}
}
