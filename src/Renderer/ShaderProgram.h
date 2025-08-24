#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>

namespace Renderer
{
	class CShaderProgram
	{
	public:
		CShaderProgram(const std::string& strVertexShader, const std::string& strFragmentShader);
		~CShaderProgram();

		bool isCompiled() const {	return m_bIsCompiled;	}
		void use() const;
		void setInt(const std::string& strName, const GLint iValue);
		void setMatrix4(const std::string& strName, const glm::mat4& matrix);

		CShaderProgram() = delete; // удаляем конструктор по умолчанию
		CShaderProgram(CShaderProgram&) = delete; // удаляем конструктор копирования
		CShaderProgram& operator=(const CShaderProgram&) = delete; // удаляем оператор присваивания через копирования

		CShaderProgram(CShaderProgram&& shaderProgram) noexcept; // конструктор перемещения
		CShaderProgram& operator=(CShaderProgram&& shaderProgram) noexcept; // оператор присваивания через перемещение
		


	private:
		bool createShader(const std::string& strSource, const GLenum eShaderType,
			GLuint& iShaderID);


		bool m_bIsCompiled = false; // флаг успеха компиляции шейдерной программы
		GLuint m_iID = 0; // id шейдерной программы
	};
};

