#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>

namespace RenderEngine
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& strVertexShader, const std::string& strFragmentShader);
		~ShaderProgram();

		bool isCompiled() const {	return m_bIsCompiled;	}
		void use() const;
		void setInt(const std::string& strName, const GLint iValue);
		void setFloat(const std::string& strName, const GLfloat fValue);
		void setMatrix4(const std::string& strName, const glm::mat4& matrix);

		ShaderProgram() = delete; // ������� ����������� �� ���������
		ShaderProgram(ShaderProgram&) = delete; // ������� ����������� �����������
		ShaderProgram& operator=(const ShaderProgram&) = delete; // ������� �������� ������������ ����� �����������

		ShaderProgram(ShaderProgram&& shaderProgram) noexcept; // ����������� �����������
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept; // �������� ������������ ����� �����������
		


	private:
		bool createShader(const std::string& strSource, const GLenum eShaderType,
			GLuint& iShaderID);


		bool m_bIsCompiled = false; // ���� ������ ���������� ��������� ���������
		GLuint m_iID = 0; // id ��������� ���������
	};
};

