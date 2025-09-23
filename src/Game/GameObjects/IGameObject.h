#pragma once
#include <glm/vec2.hpp>

class IGameObject 
{
public:
	IGameObject(const glm::vec2& position, const glm::vec2& size, const float fRotation, const float fLayer);
	virtual void render() const = 0;
	virtual void update(const double delta) {}
	virtual ~IGameObject();

	virtual glm::vec2& getCurrentPosition() {return m_position;}
	virtual glm::vec2& getCurrentDirection() {return m_direction;}
	virtual double getCurrentVelocity() {return m_dVelocity;}

	virtual void setVelocity(const double dVelocity);


protected:
	glm::vec2 m_position;
	glm::vec2 m_size;
	float m_fRotation;
	float m_fLayer;

	glm::vec2 m_direction;
	double m_dVelocity;
};
