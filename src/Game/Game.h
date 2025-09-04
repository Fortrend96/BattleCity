#pragma once
#include <array>

#include <glm/vec2.hpp>

class CGame 
{
public:
	CGame(const glm::ivec2& windowSize);
	~CGame();

	void render();
	void update(const uint64_t delta);
	void setKey(const int key, const int action);
	bool init();

private:
	enum class EGameState {
		Active,
		Pause
	};

	EGameState m_eCurrentGameState;
	std::array<bool, 349> m_keys;
	glm::ivec2 m_windowSize;

};