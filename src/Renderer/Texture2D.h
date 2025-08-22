#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer
{
	class CTexture2D
	{
	public:
		CTexture2D(const GLuint iWidth, const GLuint iHeight, const unsigned char* pData,
			const unsigned int nChannels = 4, 
			const GLenum eFilter = GL_LINEAR,
			const GLenum eWrapMode = GL_CLAMP_TO_EDGE);

		~CTexture2D();

		CTexture2D() = delete;
		CTexture2D(const CTexture2D&) = delete;
		CTexture2D& operator=(const CTexture2D&) = delete;

		CTexture2D(CTexture2D&& texture2D) noexcept;
		CTexture2D& operator=(CTexture2D&& texture2D) noexcept;

		void bind() const;



	private:
		GLuint m_iID; // id текстуры
		GLenum m_eMode; // режим (зависит от количества каналов)
		unsigned int m_iWidth; // ширина
		unsigned int m_iHeight; // высота


	};
}
