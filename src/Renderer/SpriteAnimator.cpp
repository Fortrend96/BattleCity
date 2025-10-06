#include "SpriteAnimator.h"
#include "Sprite.h"

namespace RenderEngine
{
	CSpriteAnimator::CSpriteAnimator(std::shared_ptr<CSprite> pSprite)
		: m_pSprite(pSprite)
		, m_currentFrame(0)
		, m_currentFrameDuration(pSprite->getFrameDuration(m_currentFrame))
		, m_currentAnimationTime(0)
		, m_totalDuration(0)
	{
		for (size_t currentFrameId = 0; currentFrameId < m_pSprite->getFramesCount(); ++currentFrameId)
		{
			m_totalDuration += m_pSprite->getFrameDuration(currentFrameId);
		}
	}

	void CSpriteAnimator::update(const double delta)
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

	void CSpriteAnimator::reset()
	{
		m_currentFrame = 0;
		m_currentFrameDuration = m_pSprite->getFrameDuration(0);
		m_currentAnimationTime = 0;
	}
}
