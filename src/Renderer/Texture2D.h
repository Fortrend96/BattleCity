#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <string>
#include <map>

namespace RenderEngine
{
	class Texture2D
	{
	public:
		struct SubTexture2D
		{

			glm::vec2 leftBottomUV;
			glm::vec2 rightTopUV;

			SubTexture2D(const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV)
				: leftBottomUV(_leftBottomUV)
				, rightTopUV(_rightTopUV)
			{
			}

			SubTexture2D()
				: leftBottomUV(0.f)
				, rightTopUV(1.f)
			{
			}
		};



		Texture2D(const GLuint iWidth, const GLuint iHeight, const unsigned char* pData,
			const unsigned int nChannels = 4, 
			const GLenum eFilter = GL_LINEAR,
			const GLenum eWrapMode = GL_CLAMP_TO_EDGE);

		~Texture2D();

		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;

		Texture2D(Texture2D&& texture2D) noexcept;
		Texture2D& operator=(Texture2D&& texture2D) noexcept;

		void bind() const;

		void addSubTexture(std::string strName, const glm::vec2& leftBottomUV,
			const glm::vec2& rightTopUV);

		const SubTexture2D& getSubTexture(const std::string& name) const;
		unsigned int width() const { return m_iWidth; }
		unsigned int height() const { return m_iHeight; }

	private:
		GLuint m_iID; // id текстуры
		GLenum m_eMode; // режим (зависит от количества каналов)
		unsigned int m_iWidth; // ширина
		unsigned int m_iHeight; // высота

		std::map<std::string, SubTexture2D> m_subTextures;

	};
}
