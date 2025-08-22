#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include <sstream>
#include <fstream>
#include <iostream>

CResourceManager::CResourceManager(const std::string& strExecutablePath)
{
	size_t found = strExecutablePath.find_last_of("/\\"); // ищем положение последнего слэша в строке пути
	m_strPath = strExecutablePath.substr(0, found);
}


std::string CResourceManager::getFileString(const std::string& strRelativeFilePath) const 
{
	std::fstream f;
	f.open(m_strPath + "/" + strRelativeFilePath.c_str(), std::ios::in | std::ios::binary);

	if (!f.is_open())
	{
		std::cerr << "Failed to open file: " << strRelativeFilePath << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}

std::shared_ptr<Renderer::CShaderProgram> CResourceManager::loadShaders(
	const std::string& strShaderName,
	const std::string& strVertexShaderPath, 
	const std::string& strFragmentShaderPath
)
{
	std::string strVertexShader = getFileString(strVertexShaderPath); // путь к файлу с вертексным шейдером

	if (strVertexShader.empty())
	{
		std::cerr << "No vertex shader!" << std::endl;
		return nullptr;
	}

	std::string strFragmentShader = getFileString(strFragmentShaderPath); // путь к файлу с фрагментным шейдером

	if (strFragmentShader.empty())
	{
		std::cerr << "No fragment shader!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::CShaderProgram>& pNewShaderProgram = 
		m_shaderPrograms.emplace(strShaderName, std::make_shared<Renderer::CShaderProgram>(strVertexShader, strFragmentShader)).first->second;

	if (!pNewShaderProgram->isCompiled())
	{
		std::cerr << "Cant load shader program!n" <<
			"Vertex:" << strVertexShaderPath << "\n" <<
			"Fragment" << strFragmentShaderPath << "\n" << std::endl;
		
		return nullptr;
	}

	return pNewShaderProgram;
}

std::shared_ptr<Renderer::CShaderProgram> CResourceManager::getShaderProgram(const std::string& strShaderName)
{
	TShaderProgramsMap::const_iterator it = m_shaderPrograms.find(strShaderName);

	if (it != m_shaderPrograms.end())
	{
		return it->second;
	}
	
	std::cerr << "Cant find the shader program: " << strShaderName << ".\n";
	return nullptr;
}