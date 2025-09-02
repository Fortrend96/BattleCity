#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include <sstream>
#include <fstream>
#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

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


std::shared_ptr<Renderer::CTexture2D> CResourceManager::loadTexture(const std::string& strTextureName, const std::string& strTexturePath)
{
	int nChannels = 0;
	int iWidth = 0;
	int iHeight = 0;

	stbi_set_flip_vertically_on_load(true); // устнавливаем загрузку данных снизу вверх

	unsigned char* pPixels = stbi_load(std::string(m_strPath + "/" + strTexturePath).c_str(), &iWidth, &iHeight, &nChannels, 0);

	if (!pPixels)
	{
		std::cerr << "Cant load image: " << strTexturePath << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::CTexture2D> pNewTexture = m_textures.emplace(strTextureName, 
																			std::make_shared<Renderer::CTexture2D>(
																					iWidth, 
																					iHeight, 
																					pPixels, 
																					nChannels, 
																					GL_NEAREST, 
																					GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pPixels);

	return pNewTexture;
}

std::shared_ptr<Renderer::CTexture2D> CResourceManager::getTexture(const std::string& strTextureName)
{
	TTexturesMap::const_iterator it = m_textures.find(strTextureName);

	if (it != m_textures.end())
	{
		return it->second;
	}

	std::cerr << "Cant find the texture: " << strTextureName << ".\n";
	return nullptr;
}

std::shared_ptr<Renderer::CSprite> CResourceManager::loadSprite(const std::string& strSpriteName,
																	const std::string& strTextureName,
																	const std::string& strShaderName,
																	const unsigned int iSpriteWidth,
																	const unsigned int iSpriteHeight,
																	const std::string& strSubTextureName)
{
	auto pTexture = getTexture(strTextureName);
	if (!pTexture)
	{
		std::cerr << "Can't find the texture: " << strTextureName << " for the sprite: " << strSpriteName << std::endl;
	}

	auto pShader = getShaderProgram(strShaderName);
	if (!pShader)
	{
		std::cerr << "Can't find the shader: " << strShaderName << " for the sprite: " << strSpriteName << std::endl;
	}

	std::shared_ptr<Renderer::CSprite> pNewSprite = m_sprites.emplace(strTextureName, std::make_shared<Renderer::CSprite>(pTexture,
		strSubTextureName,
		pShader,
		glm::vec2(0.f, 0.f),
		glm::vec2(iSpriteWidth, iSpriteHeight))).first->second;

	return pNewSprite;

}

std::shared_ptr<Renderer::CSprite> CResourceManager::getSprite(const std::string& strSpriteName)
{
	TSpritesMap::const_iterator it = m_sprites.find(strSpriteName);
	if (it != m_sprites.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the sprite: " << strSpriteName << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::CTexture2D> CResourceManager::loadTextureAtlas(std::string strTextureName,
	std::string strTexturePath,
	const std::vector<std::string> subTextures,
	const unsigned int iSubTextureWidth,
	const unsigned int iSubTextureHeight)
{
	auto pTexture = loadTexture(std::move(strTextureName), std::move(strTexturePath));
	if (pTexture)
	{
		const unsigned int textureWidth = pTexture->width();
		const unsigned int textureHeight = pTexture->height();
		unsigned int currentTextureOffsetX = 0;
		unsigned int currentTextureOffsetY = textureHeight;

		for (auto& currentSubTextureName : subTextures)
		{
			glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX) / textureWidth, static_cast<float>(currentTextureOffsetY - iSubTextureHeight) / textureHeight);
			glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + iSubTextureWidth) / textureWidth, static_cast<float>(currentTextureOffsetY) / textureHeight);
			pTexture->addSubTexture(std::move(currentSubTextureName), leftBottomUV, rightTopUV);

			currentTextureOffsetX += iSubTextureWidth;
			if (currentTextureOffsetX >= textureWidth)
			{
				currentTextureOffsetX = 0;
				currentTextureOffsetY -= iSubTextureHeight;
			}
		}
	}
	return pTexture;
}