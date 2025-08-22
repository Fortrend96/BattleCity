#pragma once
#include <string>
#include <memory>
#include <map>

namespace Renderer 
{
	class CShaderProgram;
	class CTexture2D;

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

	std::shared_ptr<Renderer::CShaderProgram> getShaderProgram(const std::string& strShaderName); // получение шейдерной программы

	std::shared_ptr<Renderer::CTexture2D> loadTexture(const std::string& strTextureName, const std::string& strTexturePath); // загрузка текстуры
	std::shared_ptr<Renderer::CTexture2D> getTexture(const std::string& strTextureName); // получение текстуры


private:
	std::string getFileString(const std::string& strRelativeFilePath) const;  // получение пути к файлу с шейдером

	using TShaderProgramsMap = std::map<const std::string, std::shared_ptr<Renderer::CShaderProgram>>;
	using TTexturesMap = std::map<const std::string, std::shared_ptr<Renderer::CTexture2D>>;

	TShaderProgramsMap m_shaderPrograms;
	TTexturesMap m_textures;

	std::string m_strPath;
};