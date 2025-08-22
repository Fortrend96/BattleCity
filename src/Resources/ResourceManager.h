#pragma once
#include <string>
#include <memory>
#include <map>

namespace Renderer 
{
	class CShaderProgram;
	class CTexture2D;

}

// �������� ��������
class CResourceManager {
public:
	explicit CResourceManager(const std::string& strExecutablePath);
	~CResourceManager() = default;

	CResourceManager(const CResourceManager&) = delete;
	CResourceManager& operator=(const CResourceManager&) = delete;

	CResourceManager(CResourceManager&&) = delete;
	CResourceManager& operator=(CResourceManager&&) = delete;

	std::shared_ptr<Renderer::CShaderProgram> loadShaders(const std::string& strShaderName, 
		const std::string& strVertexShaderPath, const std::string& strFragmentShaderPath); // �������� ��������� ���������

	std::shared_ptr<Renderer::CShaderProgram> getShaderProgram(const std::string& strShaderName); // ��������� ��������� ���������

	std::shared_ptr<Renderer::CTexture2D> loadTexture(const std::string& strTextureName, const std::string& strTexturePath); // �������� ��������
	std::shared_ptr<Renderer::CTexture2D> getTexture(const std::string& strTextureName); // ��������� ��������


private:
	std::string getFileString(const std::string& strRelativeFilePath) const;  // ��������� ���� � ����� � ��������

	using TShaderProgramsMap = std::map<const std::string, std::shared_ptr<Renderer::CShaderProgram>>;
	using TTexturesMap = std::map<const std::string, std::shared_ptr<Renderer::CTexture2D>>;

	TShaderProgramsMap m_shaderPrograms;
	TTexturesMap m_textures;

	std::string m_strPath;
};