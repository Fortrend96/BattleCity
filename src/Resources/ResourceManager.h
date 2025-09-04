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
	class CAnimatedSprite;
}

// менеджер ресурсов
class CResourceManager {
public:
	static void setExecutablePath(const std::string& strExecutablePath);
	static void unloadAllResources();

	CResourceManager() = delete;
	~CResourceManager() = delete;
	

	CResourceManager(const CResourceManager&) = delete;
	CResourceManager& operator=(const CResourceManager&) = delete;

	CResourceManager(CResourceManager&&) = delete;
	CResourceManager& operator=(CResourceManager&&) = delete;

	static std::shared_ptr<Renderer::CShaderProgram> loadShaders(const std::string& strShaderName, 
		const std::string& strVertexShaderPath, const std::string& strFragmentShaderPath); // загрузка шейдерной программы

	static std::shared_ptr<Renderer::CShaderProgram> getShaderProgram(const std::string& strShaderName); // получение шейдерной программы

	static std::shared_ptr<Renderer::CTexture2D> loadTexture(const std::string& strTextureName, const std::string& strTexturePath); // загрузка текстуры
	static std::shared_ptr<Renderer::CTexture2D> getTexture(const std::string& strTextureName); // получение текстуры

	static std::shared_ptr<Renderer::CSprite> loadSprite(const std::string& strSpriteName,
													const std::string& strTextureName,
													const std::string& strShaderName,
													const unsigned int iSpriteWidth,
													const unsigned int iSpriteHeight,
													const std::string& strSubTextureName = "default"); // загрузка спрайта
	
	static std::shared_ptr<Renderer::CSprite> getSprite(const std::string& strSpriteName); // получение спрайта


	static std::shared_ptr<Renderer::CAnimatedSprite> loadAnimatedSprite(const std::string& strSpriteName,
		const std::string& strTextureName,
		const std::string& strShaderName,
		const unsigned int iSpriteWidth,
		const unsigned int iSpriteHeight,
		const std::string& strSubTextureName = "default"); // загрузка анимированного спрайта

	static std::shared_ptr<Renderer::CAnimatedSprite> getAnimatedSprite(const std::string& strSpriteName); // получение анимированного спрайта


	static std::shared_ptr<Renderer::CTexture2D> loadTextureAtlas( std::string strTextureName,
															std::string strTexturePath,
															std::vector<std::string> subTextures,
															const unsigned int iSubTextureWidth,
															const unsigned int iSubTextureHeight);// загрузка текстурного атласа



	
private:
	static std::string getFileString(const std::string& strRelativeFilePath);  // получение пути к файлу с шейдером

	using TShaderProgramsMap = std::map<const std::string, std::shared_ptr<Renderer::CShaderProgram>>;
	using TTexturesMap = std::map<const std::string, std::shared_ptr<Renderer::CTexture2D>>;
	using TSpritesMap = std::map<const std::string, std::shared_ptr<Renderer::CSprite>>;
	using TAnimatedSpritesMap = std::map<const std::string, std::shared_ptr<Renderer::CAnimatedSprite>>;

	static TShaderProgramsMap m_shaderPrograms;
	static TTexturesMap m_textures;
	static TSpritesMap m_sprites;
	static TAnimatedSpritesMap m_animatedSprites;

	static std::string m_strPath;
};