#include "BrickWall.h"
#include "../../Renderer/Sprite.h"


CBrickWall::CBrickWall(const std::shared_ptr<RenderEngine::CSprite> pSprite, const glm::vec2& position, const glm::vec2& size, const float fRotation)
	: IGameObject(position, size, fRotation)
	, m_pCurSprite(std::move(pSprite))
{

}

void CBrickWall::render() const
{
	m_pCurSprite->render(m_position, m_size, m_fRotation);
}

void CBrickWall::update(const uint64_t delta)
{

}
