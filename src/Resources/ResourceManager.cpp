#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>


#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"


ResourceManager::TShaderProgramsMap	ResourceManager::m_shaderPrograms;
ResourceManager::TTexturesMap			ResourceManager::m_textures;
ResourceManager::TSpritesMap			ResourceManager::m_sprites;

std::vector<std::vector<std::string>> ResourceManager::m_levels;

std::string ResourceManager::m_strPath;

void ResourceManager::setExecutablePath(const std::string& strExecutablePath)
{
	size_t found = strExecutablePath.find_last_of("/\\"); // ищем положение последнего слэша в строке пути
	m_strPath = strExecutablePath.substr(0, found);
}

void ResourceManager::unloadAllResources()
{
	m_shaderPrograms.clear();
	m_textures.clear();
	m_sprites.clear();
}

std::string ResourceManager::getFileString(const std::string& strRelativeFilePath)
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

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::loadShaders(
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

	std::shared_ptr<RenderEngine::ShaderProgram>& pNewShaderProgram = 
		m_shaderPrograms.emplace(strShaderName, std::make_shared<RenderEngine::ShaderProgram>(strVertexShader, strFragmentShader)).first->second;

	if (!pNewShaderProgram->isCompiled())
	{
		std::cerr << "Cant load shader program!n" <<
			"Vertex:" << strVertexShaderPath << "\n" <<
			"Fragment" << strFragmentShaderPath << "\n" << std::endl;
		
		return nullptr;
	}

	return pNewShaderProgram;
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::getShaderProgram(const std::string& strShaderName)
{
	TShaderProgramsMap::const_iterator it = m_shaderPrograms.find(strShaderName);

	if (it != m_shaderPrograms.end())
	{
		return it->second;
	}
	
	std::cerr << "Cant find the shader program: " << strShaderName << ".\n";
	return nullptr;
}


std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTexture(const std::string& strTextureName, const std::string& strTexturePath)
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

	std::shared_ptr<RenderEngine::Texture2D> pNewTexture = m_textures.emplace(strTextureName, 
																			std::make_shared<RenderEngine::Texture2D>(
																					iWidth, 
																					iHeight, 
																					pPixels, 
																					nChannels, 
																					GL_NEAREST, 
																					GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pPixels);

	return pNewTexture;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::getTexture(const std::string& strTextureName)
{
	TTexturesMap::const_iterator it = m_textures.find(strTextureName);

	if (it != m_textures.end())
	{
		return it->second;
	}

	std::cerr << "Cant find the texture: " << strTextureName << ".\n";
	return nullptr;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::loadSprite(const std::string& strSpriteName,
																	const std::string& strTextureName,
																	const std::string& strShaderName,
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

	std::shared_ptr<RenderEngine::Sprite> pNewSprite = m_sprites.emplace(strSpriteName, std::make_shared<RenderEngine::Sprite>(pTexture,
		strSubTextureName,
		pShader)).first->second;

	return pNewSprite;

}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::getSprite(const std::string& strSpriteName)
{
	TSpritesMap::const_iterator it = m_sprites.find(strSpriteName);
	if (it != m_sprites.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the sprite: " << strSpriteName << std::endl;
	return nullptr;
}


std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTextureAtlas(std::string strTextureName,
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
			glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX + 0.01f) / textureWidth, static_cast<float>(currentTextureOffsetY - iSubTextureHeight + 0.01f) / textureHeight);
			glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + iSubTextureWidth - 0.01f) / textureWidth, static_cast<float>(currentTextureOffsetY - 0.01f) / textureHeight);
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

bool ResourceManager::loadJSONResources(const std::string& strJSONPath)
{
	const std::string JSONString = getFileString(strJSONPath);
	if (JSONString.empty())
	{
		std::cerr << "No JSON resources file!" << std::endl;
		return false;
	}

	rapidjson::Document document;
	rapidjson::ParseResult parseResult = document.Parse(JSONString.c_str());
	if (!parseResult)
	{
		std::cerr << "JSON parse error: " << rapidjson::GetParseError_En(parseResult.Code()) << "(" << parseResult.Offset() << ")" << std::endl;
		std::cerr << "In JSON file: " << strJSONPath << std::endl;
		return false;
	}

	auto shadersIt = document.FindMember("shaders");
	if (shadersIt != document.MemberEnd())
	{
		for (const auto& currentShader : shadersIt->value.GetArray())
		{
			const std::string name = currentShader["name"].GetString();
			const std::string filePath_v = currentShader["filePath_v"].GetString();
			const std::string filePath_f = currentShader["filePath_f"].GetString();
			loadShaders(name, filePath_v, filePath_f);
		}
	}

	auto textureAtlasesIt = document.FindMember("textureAtlases");
	if (textureAtlasesIt != document.MemberEnd())
	{
		for (const auto& currentTextrueAtlas : textureAtlasesIt->value.GetArray())
		{
			const std::string name = currentTextrueAtlas["name"].GetString();
			const std::string filePath = currentTextrueAtlas["filePath"].GetString();
			const unsigned int subTextureWidht = currentTextrueAtlas["subTextureWidth"].GetUint();
			const unsigned int subTextureHeight = currentTextrueAtlas["subTextureHeight"].GetUint();

			const auto subTexturesArray = currentTextrueAtlas["subTextures"].GetArray();
			std::vector<std::string> subTextures;
			subTextures.reserve(subTexturesArray.Size());
			for (const auto& currentSubTexture : subTexturesArray)
			{
				subTextures.emplace_back(currentSubTexture.GetString());
			}
			loadTextureAtlas(name, filePath, std::move(subTextures), subTextureWidht, subTextureHeight);
		}
	}

	auto spritesIt = document.FindMember("sprites");
	if (spritesIt != document.MemberEnd())
	{
		for (const auto& currentSprite : spritesIt->value.GetArray())
		{
			const std::string name = currentSprite["name"].GetString();
			const std::string textureAtlas = currentSprite["textureAtlas"].GetString();
			const std::string shader = currentSprite["shader"].GetString();
			const std::string subTexture = currentSprite["initialSubTexture"].GetString();

			auto pSprite = loadSprite(name, textureAtlas, shader, subTexture);

			if (!pSprite)
			{
				continue;
			}

			auto framesIt = currentSprite.FindMember("frames");
			if (framesIt != currentSprite.MemberEnd())
			{
				const auto framesArray = framesIt->value.GetArray();
				std::vector<RenderEngine::Sprite::FrameDescription> frameDescriptions;
				frameDescriptions.reserve(framesArray.Size());

				for (const auto& currentFrame : framesArray)
				{
					const std::string subTextureStr = currentFrame["subTexture"].GetString();
					const double duration = currentFrame["duration"].GetDouble();
					const auto pTextureAtlas = getTexture(textureAtlas);
					const auto pSubTexture = pTextureAtlas->getSubTexture(subTextureStr);
					frameDescriptions.emplace_back(pSubTexture.leftBottomUV, pSubTexture.rightTopUV,duration);
				}
				pSprite->insertFrames(std::move(frameDescriptions));

			}
		}
	}

	auto levelsIt = document.FindMember("levels");
	if (levelsIt != document.MemberEnd())
	{
		for (const auto& currentLevel : levelsIt->value.GetArray())
		{
			const auto description = currentLevel["description"].GetArray();
			std::vector<std::string> levelRows;
			levelRows.reserve(description.Size());
			size_t maxLength = 0;
			for (const auto& currentRow : description)
			{
				levelRows.emplace_back(currentRow.GetString());
				if (maxLength < levelRows.back().length())
				{
					maxLength = levelRows.back().length();
				}
			}

			for (auto& curRow : levelRows)
			{
				while (curRow.length() < maxLength)
				{
					curRow.append("D");
				}
			}
			m_levels.emplace_back(std::move(levelRows));
		}

		
	}

	return true;
}