#pragma once
#include <glad/glad.h>

namespace Renderer
{
	class CVertexBuffer 
	{
	public:
		CVertexBuffer();
		~CVertexBuffer();

		CVertexBuffer(const CVertexBuffer&) = delete;
		CVertexBuffer& operator=(const CVertexBuffer&) = delete;

		CVertexBuffer(CVertexBuffer&& vertexBuffer) noexcept;
		CVertexBuffer& operator=(CVertexBuffer&& vertexBuffer) noexcept;

		void init(const void* pData, const unsigned int size);
		void update(const void* pData, const unsigned int size) const;

		void bind() const;
		void unbind() const;

	private:
		GLuint m_id;
	};
}
