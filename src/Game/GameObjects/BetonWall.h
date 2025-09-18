#pragma once

#include "IGameObject.h"
#include <memory>
#include <array>

namespace RenderEngine 
{
	class CSprite;
}

class CBetonWall : public IGameObject
{
public:

	enum class EBetonWallType
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

	enum class EBlockState
	{
		Enabled = 0,
		Destroyed
	};

	enum class EBlockLocation {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	CBetonWall(const EBetonWallType eBetonWallType, const glm::vec2& position, const glm::vec2& size, 
			const float fRotation, const float fLayer);
	virtual void render() const override;
	virtual void update(const uint64_t delta) override;

	

private:
	void renderBlock(const EBlockLocation eBlockLocation) const;

	std::array<EBlockState, 4> m_eCurrentBlockState;
	std::shared_ptr<RenderEngine::CSprite> m_sprite;
	std::array<glm::vec2, 4> m_blockOffsets;

};
