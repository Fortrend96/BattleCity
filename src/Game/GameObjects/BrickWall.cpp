#include "BrickWall.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

CBrickWall::CBrickWall(const EBrickWallType eBrickWallType,
						const glm::vec2& position, 
						const glm::vec2& size, 
						const float fRotation, const float fLayer)
						: IGameObject(IGameObject::EObjectType::BrickWall, position, size, fRotation, fLayer)
						, m_eCurrentBrickState{EBrickState::Destroyed,
												EBrickState::Destroyed, 
												EBrickState::Destroyed, 
												EBrickState::Destroyed }
                        , m_blockOffsets{ glm::vec2(0, m_size.y / 2.f),
                            glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
                            glm::vec2(0, 0),
                            glm::vec2(m_size.x / 2.f, 0) }
{
    m_sprites[static_cast<size_t>(EBrickState::All)]                    = CResourceManager::getSprite("brickWall_All");
    m_sprites[static_cast<size_t>(EBrickState::TopLeft)]                = CResourceManager::getSprite("brickWall_TopLeft");
    m_sprites[static_cast<size_t>(EBrickState::TopRight)]               = CResourceManager::getSprite("brickWall_TopRight");
    m_sprites[static_cast<size_t>(EBrickState::Top)]                    = CResourceManager::getSprite("brickWall_Top");
    m_sprites[static_cast<size_t>(EBrickState::BottomLeft)]             = CResourceManager::getSprite("brickWall_BottomLeft");
    m_sprites[static_cast<size_t>(EBrickState::Left)]                   = CResourceManager::getSprite("brickWall_Left");
    m_sprites[static_cast<size_t>(EBrickState::TopRight_BottomLeft)]    = CResourceManager::getSprite("brickWall_TopRight_BottomLeft");
    m_sprites[static_cast<size_t>(EBrickState::Top_BottomLeft)]         = CResourceManager::getSprite("brickWall_Top_BottomLeft");
    m_sprites[static_cast<size_t>(EBrickState::BottomRight)]            = CResourceManager::getSprite("brickWall_BottomRight");
    m_sprites[static_cast<size_t>(EBrickState::TopLeft_BottomRight)]    = CResourceManager::getSprite("brickWall_TopLeft_BottomRight");
    m_sprites[static_cast<size_t>(EBrickState::Right)]                  = CResourceManager::getSprite("brickWall_Right");
    m_sprites[static_cast<size_t>(EBrickState::Top_BottomRight)]        = CResourceManager::getSprite("brickWall_Top_BottomRight");
    m_sprites[static_cast<size_t>(EBrickState::Bottom)]                 = CResourceManager::getSprite("brickWall_Bottom");
    m_sprites[static_cast<size_t>(EBrickState::TopLeft_Bottom)]         = CResourceManager::getSprite("brickWall_TopLeft_Bottom");
    m_sprites[static_cast<size_t>(EBrickState::TopRight_Bottom)]        = CResourceManager::getSprite("brickWall_TopRight_Bottom");

    switch (eBrickWallType)
    {
    case EBrickWallType::All:
        m_eCurrentBrickState.fill(EBrickState::All);
        m_colliders.emplace_back(glm::vec2(0), m_size);
        break;
    case EBrickWallType::Top:
        m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
        m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
        m_colliders.emplace_back(glm::vec2(0, m_size.y / 2), m_size);
        break;
    case EBrickWallType::Bottom:
        m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
        m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
        m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x, m_size.y / 2));
        break;
    case EBrickWallType::Left:
        m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
        m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
        m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y));
        break;
    case EBrickWallType::Right:
        m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
        m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
        m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0), m_size);
        break;
    case EBrickWallType::TopLeft:
        m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
        m_colliders.emplace_back(glm::vec2(0, m_size.y / 2), glm::vec2(m_size.x / 2, m_size.y));
        break;
    case EBrickWallType::TopRight:
        m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
        m_colliders.emplace_back(glm::vec2(m_size.x / 2, m_size.y / 2), m_size);
        break;
    case EBrickWallType::BottomLeft:
        m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
        m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y / 2));
        break;
    case EBrickWallType::BottomRight:
        m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
        m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0), glm::vec2(m_size.x, m_size.y / 2));
        break;
    }


}

void CBrickWall::renderBrick(const EBrickLocation eBrickLocation) const
{
    const EBrickState state = m_eCurrentBrickState[static_cast<size_t>(eBrickLocation)];
    if (state != EBrickState::Destroyed)
    {
        m_sprites[static_cast<size_t>(state)]->render(m_position + m_blockOffsets[static_cast<size_t>(eBrickLocation)], 
            m_size / 2.f, m_fRotation, m_fLayer, m_fLayer);
    }
}

void CBrickWall::render() const
{
    renderBrick(EBrickLocation::TopLeft);
    renderBrick(EBrickLocation::TopRight);
    renderBrick(EBrickLocation::BottomLeft);
    renderBrick(EBrickLocation::BottomRight);
}

void CBrickWall::update(const double delta)
{

}
