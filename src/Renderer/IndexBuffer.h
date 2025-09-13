#pragma once
#include <glad/glad.h>

namespace RenderEngine
{
	class CIndexBuffer 
	{
	public:
		CIndexBuffer();
		~CIndexBuffer();

		CIndexBuffer(const CIndexBuffer&) = delete;
		CIndexBuffer& operator=(const CIndexBuffer&) = delete;

		CIndexBuffer(CIndexBuffer&& indexBuffer) noexcept;
		CIndexBuffer& operator=(CIndexBuffer&& indexBuffer) noexcept;

		void init(const void* pData, const unsigned int iCount);
		void bind() const;
		void unbind() const;

		unsigned int getCount() const {
			return m_iCount;
		}

	private:
		GLuint m_id;
		unsigned int m_iCount;
	};
}
