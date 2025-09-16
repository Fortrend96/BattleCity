#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>

namespace RenderEngine 
{
	class CShaderProgram;
	class CTexture2D;
	class CSprite;
	class CAnimatedSprite;
}

// �������� ��������
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

	static std::shared_ptr<RenderEngine::CShaderProgram> loadShaders(const std::string& strShaderName, 
		const std::string& strVertexShaderPath, const std::string& strFragmentShaderPath); // �������� ��������� ���������

	static std::shared_ptr<RenderEngine::CShaderProgram> getShaderProgram(const std::string& strShaderName); // ��������� ��������� ���������

	static std::shared_ptr<RenderEngine::CTexture2D> loadTexture(const std::string& strTextureName, const std::string& strTexturePath); // �������� ��������
	static std::shared_ptr<RenderEngine::CTexture2D> getTexture(const std::string& strTextureName); // ��������� ��������

	static std::shared_ptr<RenderEngine::CSprite> loadSprite(const std::string& strSpriteName,
													const std::string& strTextureName,
													const std::string& strShaderName,
													const std::string& strSubTextureName = "default"); // �������� �������
	
	static std::shared_ptr<RenderEngine::CSprite> getSprite(const std::string& strSpriteName); // ��������� �������


	static std::shared_ptr<RenderEngine::CAnimatedSprite> loadAnimatedSprite(const std::string& strSpriteName,
		const std::string& strTextureName,
		const std::string& strShaderName,
		const std::string& strSubTextureName = "default"); // �������� �������������� �������

	static std::shared_ptr<RenderEngine::CAnimatedSprite> getAnimatedSprite(const std::string& strSpriteName); // ��������� �������������� �������


	static std::shared_ptr<RenderEngine::CTexture2D> loadTextureAtlas( std::string strTextureName,
															std::string strTexturePath,
															std::vector<std::string> subTextures,
															const unsigned int iSubTextureWidth,
															const unsigned int iSubTextureHeight);// �������� ����������� ������

	static bool loadJSONResources(const std::string& strJSONPath);

	static const std::vector<std::vector<std::string>>& getLevels() {
		return m_levels
			;
	}
	
private:
	static std::string getFileString(const std::string& strRelativeFilePath);  // ��������� ���� � ����� � ��������

	using TShaderProgramsMap = std::map<const std::string, std::shared_ptr<RenderEngine::CShaderProgram>>;
	using TTexturesMap = std::map<const std::string, std::shared_ptr<RenderEngine::CTexture2D>>;
	using TSpritesMap = std::map<const std::string, std::shared_ptr<RenderEngine::CSprite>>;
	using TAnimatedSpritesMap = std::map<const std::string, std::shared_ptr<RenderEngine::CAnimatedSprite>>;

	static TShaderProgramsMap m_shaderPrograms;
	static TTexturesMap m_textures;
	static TSpritesMap m_sprites;
	static TAnimatedSpritesMap m_animatedSprites;

	static std::vector<std::vector<std::string>> m_levels;

	static std::string m_strPath;
};