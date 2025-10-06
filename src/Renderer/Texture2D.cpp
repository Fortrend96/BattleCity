#include "Texture2D.h"

namespace RenderEngine {
	Texture2D::Texture2D(const GLuint iWidth, const GLuint iHeight, const unsigned char* pData,
		const unsigned int nChannels,
		const GLenum eFilter,
		const GLenum eWrapMode) :
			m_iWidth(iWidth), m_iHeight(iHeight)
	{
		switch (nChannels)
		{
		case 4:
			m_eMode = GL_RGBA;
			break;
		case 3:
			m_eMode = GL_RGB;
			break;
		default:
			m_eMode = GL_RGB;
			break;
		}


		glGenTextures(1, &m_iID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_iID);
		glTexImage2D(GL_TEXTURE_2D, 0, m_eMode, m_iWidth, m_iHeight, 0, m_eMode, GL_UNSIGNED_BYTE, pData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, eWrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, eWrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, eFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, eFilter);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_iID);
	}

	Texture2D::Texture2D(Texture2D&& texture2D) noexcept
	{
		this->m_iID = texture2D.m_iID;
		texture2D.m_iID = 0;

		this->m_eMode = texture2D.m_eMode;
		this->m_iWidth = texture2D.m_iWidth;
		this->m_iHeight = texture2D.m_iHeight;

	}
	Texture2D& Texture2D::operator=(Texture2D&& texture2D) noexcept
	{
		glDeleteTextures(1, &m_iID);

		this->m_iID = texture2D.m_iID;
		texture2D.m_iID = 0;

		this->m_eMode = texture2D.m_eMode;
		this->m_iWidth = texture2D.m_iWidth;
		this->m_iHeight = texture2D.m_iHeight;

		return *this;
	}

	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_iID);
	}
	
	void Texture2D::addSubTexture(std::string strName, const glm::vec2& leftBottomUV,
		const glm::vec2& rightTopUV)
	{
		m_subTextures.emplace(std::move(strName), SubTexture2D(leftBottomUV, rightTopUV));
	}

	const Texture2D::SubTexture2D& Texture2D::getSubTexture(const std::string& name) const
	{
		auto it = m_subTextures.find(name);
		if (it != m_subTextures.end())
		{
			return it->second;
		}
		const static SubTexture2D defaultSubTexture;
		return defaultSubTexture;
	}

}
