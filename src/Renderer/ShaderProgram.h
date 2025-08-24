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

		CShaderProgram() = delete; // ������� ����������� �� ���������
		CShaderProgram(CShaderProgram&) = delete; // ������� ����������� �����������
		CShaderProgram& operator=(const CShaderProgram&) = delete; // ������� �������� ������������ ����� �����������

		CShaderProgram(CShaderProgram&& shaderProgram) noexcept; // ����������� �����������
		CShaderProgram& operator=(CShaderProgram&& shaderProgram) noexcept; // �������� ������������ ����� �����������
		


	private:
		bool createShader(const std::string& strSource, const GLenum eShaderType,
			GLuint& iShaderID);


		bool m_bIsCompiled = false; // ���� ������ ���������� ��������� ���������
		GLuint m_iID = 0; // id ��������� ���������
	};
};

