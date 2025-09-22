#pragma once
#include <array>
#include <memory>

#include <glm/vec2.hpp>

class CTank;
class CLevel;

class CGame 
{
public:
	CGame(const glm::ivec2& windowSize);
	~CGame();

	void render();
	void update(const uint64_t delta);
	void setKey(const int key, const int action);
	bool init();

	size_t getCurrentLevelWidth() const;
	size_t getCurrentLevelHeight() const;

private:
	enum class EGameState {
		Active,
		Pause
	};

	EGameState m_eCurrentGameState;
	std::array<bool, 349> m_keys;
	glm::ivec2 m_windowSize;

	std::unique_ptr<CTank> m_pTank;

	std::unique_ptr<CLevel> m_pLevel;

};