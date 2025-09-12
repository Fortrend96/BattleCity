#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <glad/glad.h>



namespace Renderer
{

	class CVertexArray 
	{
	public:
		CVertexArray();
		~CVertexArray();

		CVertexArray(const CVertexArray&) = delete;
		CVertexArray& operator=(const CVertexArray&) = delete;

		CVertexArray(CVertexArray&& vertexArray) noexcept;
		CVertexArray& operator=(CVertexArray&& vertexArray) noexcept;
		
		void addBuffer(const CVertexBuffer& vertexBuffer, const CVertexBufferLayout& layout);
		void bind() const;
		void unbind() const;

	private:
		GLuint m_id = 0;
		unsigned int m_iElementsCount = 0;
	};
}
