#pragma once
#include <vector>
#include <string>
#include <memory>



class IGameObject;

class CLevel 
{
public:
	CLevel(const std::vector<std::string>& levelDescription);
	void render() const;
	void update(const uint64_t delta);

	size_t getLevelWidth() const;
	size_t getLevelHeight() const;

private:
	size_t m_iWidth;
	size_t m_iHeight;

	std::vector<std::shared_ptr<IGameObject>> m_levelObjects;
};
