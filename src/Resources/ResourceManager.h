#pragma once
#include <string>
#include <memory>
#include <map>

namespace Renderer {
	class CShaderProgram;
}

// менеджер ресурсов
class CResourceManager {
public:
	explicit CResourceManager(const std::string& strExecutablePath);
	~CResourceManager() = default;

	CResourceManager(const CResourceManager&) = delete;
	CResourceManager& operator=(const CResourceManager&) = delete;

	CResourceManager(CResourceManager&&) = delete;
	CResourceManager& operator=(CResourceManager&&) = delete;

	std::shared_ptr<Renderer::CShaderProgram> loadShaders(const std::string& strShaderName,
		const std::string& strVertexShaderPath, const std::string& strFragmentShaderPath); // загрузка шейдерной программы

	std::shared_ptr<Renderer::CShaderProgram> getShaderProgram(const std::string& strShaderName); // получения шейдера
private:
	std::string getFileString(const std::string& strRelativeFilePath) const;  // получение пути к файлу с шейдером

	using TShaderProgramsMap = std::map<const std::string, std::shared_ptr<Renderer::CShaderProgram>>;
	TShaderProgramsMap m_shaderPrograms;
	std::string m_strPath;
};