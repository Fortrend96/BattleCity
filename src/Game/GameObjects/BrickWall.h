#pragma once

#include "IGameObject.h"
#include <memory>
#include <array>

namespace RenderEngine 
{
	class CSprite;
}

class CBrickWall : public IGameObject
{
public:

	enum class EBrickWallType : uint8_t 
	{
		All, 
		Top, 
		Bottom, 
		Left, 
		Right, 
		TopLeft, 
		TopRight, 
		BottomLeft,
		BottomRight
	};

	enum class EBrickState : uint8_t
	{
		All,
		TopLeft,
		TopRight,
		Top,
		BottomLeft,
		Left,
		TopRight_BottomLeft,
		Top_BottomLeft,
		BottomRight,
		TopLeft_BottomRight,
		Right,
		Top_BottomRight,
		Bottom,
		TopLeft_Bottom,
		TopRight_Bottom,
		Destroyed
	};

	enum class EBrickLocation : uint8_t {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	CBrickWall(const EBrickWallType eBrickWallType, const glm::vec2& position, const glm::vec2& size, const float fRotation, const float fLayer);
	virtual void render() const override;
	virtual void update(const uint64_t delta) override;

	

private:
	void renderBrick(const EBrickLocation eBrickLocation) const;

	std::array<EBrickState, 4> m_eCurrentBrickState;
	std::array<std::shared_ptr<RenderEngine::CSprite>, 15> m_sprites;
	std::array<glm::vec2, 4> m_blockOffsets;

};
