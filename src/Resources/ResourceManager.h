#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>

namespace Renderer 
{
	class CShaderProgram;
	class CTexture2D;
	class CSprite;
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

	std::shared_ptr<Renderer::CSprite> loadSprite(const std::string& strSpriteName,
													const std::string& strTextureName,
													const std::string& strShaderName,
													const unsigned int iSpriteWidth,
													const unsigned int iSpriteHeight,
													const std::string& strSubTextureName = "default"); // загрузка спрайта
	
	std::shared_ptr<Renderer::CSprite> getSprite(const std::string& strSpriteName); // получение спрайта

	std::shared_ptr<Renderer::CTexture2D> loadTextureAtlas( std::string strTextureName,
															std::string strTexturePath,
															std::vector<std::string> subTextures,
															const unsigned int iSubTextureWidth,
															const unsigned int iSubTextureHeight);// загрузка текстурного атласа
	
private:
	std::string getFileString(const std::string& strRelativeFilePath) const;  // получение пути к файлу с шейдером

	using TShaderProgramsMap = std::map<const std::string, std::shared_ptr<Renderer::CShaderProgram>>;
	using TTexturesMap = std::map<const std::string, std::shared_ptr<Renderer::CTexture2D>>;
	using TSpritesMap = std::map<const std::string, std::shared_ptr<Renderer::CSprite>>;

	TShaderProgramsMap m_shaderPrograms;
	TTexturesMap m_textures;
	TSpritesMap m_sprites;

	std::string m_strPath;
};