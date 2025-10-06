#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>

namespace RenderEngine 
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
}

// �������� ��������
class ResourceManager {
public:
	static void setExecutablePath(const std::string& strExecutablePath);
	static void unloadAllResources();

	ResourceManager() = delete;
	~ResourceManager() = delete;
	

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	static std::shared_ptr<RenderEngine::ShaderProgram> loadShaders(const std::string& strShaderName, 
		const std::string& strVertexShaderPath, const std::string& strFragmentShaderPath); // �������� ��������� ���������

	static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string& strShaderName); // ��������� ��������� ���������

	static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& strTextureName, const std::string& strTexturePath); // �������� ��������
	static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string& strTextureName); // ��������� ��������

	static std::shared_ptr<RenderEngine::Sprite> loadSprite(const std::string& strSpriteName,
													const std::string& strTextureName,
													const std::string& strShaderName,
													const std::string& strSubTextureName = "default"); // �������� �������
	
	static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string& strSpriteName); // ��������� �������


	static std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas( std::string strTextureName,
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

	using TShaderProgramsMap = std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>>;
	using TTexturesMap = std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>>;
	using TSpritesMap = std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>>;

	static TShaderProgramsMap m_shaderPrograms;
	static TTexturesMap m_textures;
	static TSpritesMap m_sprites;

	static std::vector<std::vector<std::string>> m_levels;

	static std::string m_strPath;
};