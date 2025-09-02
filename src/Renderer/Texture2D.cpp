#include "Texture2D.h"

namespace Renderer {
	CTexture2D::CTexture2D(const GLuint iWidth, const GLuint iHeight, const unsigned char* pData,
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

	CTexture2D::~CTexture2D()
	{
		glDeleteTextures(1, &m_iID);
	}

	CTexture2D::CTexture2D(CTexture2D&& texture2D) noexcept
	{
		this->m_iID = texture2D.m_iID;
		texture2D.m_iID = 0;

		this->m_eMode = texture2D.m_eMode;
		this->m_iWidth = texture2D.m_iWidth;
		this->m_iHeight = texture2D.m_iHeight;

	}
	CTexture2D& CTexture2D::operator=(CTexture2D&& texture2D) noexcept
	{
		glDeleteTextures(1, &m_iID);

		this->m_iID = texture2D.m_iID;
		texture2D.m_iID = 0;

		this->m_eMode = texture2D.m_eMode;
		this->m_iWidth = texture2D.m_iWidth;
		this->m_iHeight = texture2D.m_iHeight;

		return *this;
	}

	void CTexture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_iID);
	}
	
	void CTexture2D::addSubTexture(std::string strName, const glm::vec2& leftBottomUV,
		const glm::vec2& rightTopUV)
	{
		m_subTextures.emplace(std::move(strName), CSubTexture2D(leftBottomUV, rightTopUV));
	}

	const CTexture2D::CSubTexture2D& CTexture2D::getSubTexture(const std::string& name) const
	{
		auto it = m_subTextures.find(name);
		if (it != m_subTextures.end())
		{
			return it->second;
		}
		const static CSubTexture2D defaultSubTexture;
		return defaultSubTexture;
	}

}
