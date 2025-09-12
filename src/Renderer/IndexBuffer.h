#pragma once
#include <glad/glad.h>

namespace Renderer
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

		void init(const void* pData, const unsigned int size);
		void bind() const;
		void unbind() const;

	private:
		GLuint m_id;
	};
}
