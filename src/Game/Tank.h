#pragma once
#include <glm/vec2.hpp>
#include <memory>


namespace RenderEngine 
{
	class CAnimatedSprite;
}

class CTank 
{
public:
	enum class EOrientation {
		Top,
		Bottom,
		Left,
		Right
	};

	CTank(std::shared_ptr<RenderEngine::CAnimatedSprite> pSprite, const float fVelocity,
		const glm::vec2& position);

	void render() const;
	void setOrientaion(const EOrientation eOrientation);

	void move(const bool bMove);
	void update(const uint64_t delta);

private:
	EOrientation m_eOrientation;
	std::shared_ptr<RenderEngine::CAnimatedSprite> m_pSprite;
	bool m_bMove;
	float m_fVelocity;
	glm::vec2 m_position;
	glm::vec2 m_moveOffset;

};
