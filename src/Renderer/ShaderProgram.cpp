#include "ShaderProgram.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace Renderer 
{
	CShaderProgram::CShaderProgram(const std::string& strVertexShader, const std::string& strFragmentShader)
	{
		GLuint iVertexShaderID;
		if (!createShader(strVertexShader, GL_VERTEX_SHADER, iVertexShaderID))
		{
			std::cerr << "VERTEX SHADER complie time error" << std::endl;
			glDeleteShader(iVertexShaderID);
			return;
		}

		GLuint iFragmentShaderID;
		if (!createShader(strFragmentShader, GL_FRAGMENT_SHADER, iFragmentShaderID))
		{
			std::cerr << "FRAGMENT SHADER complie time error" << std::endl;
			glDeleteShader(iFragmentShaderID);
			return;
		}

		m_iID = glCreateProgram(); // ������ ����� ������ ��������� ��������� � ���������� � �������������
		glAttachShader(m_iID, iVertexShaderID); // ����������� ���������� ������ � ���������
		glAttachShader(m_iID, iFragmentShaderID); // ����������� ����������� ������ � ���������
		glLinkProgram(m_iID); // �������� ��������� ���������

		// �������� �������� ��������� ���������
		GLint iSuccess;
		glGetProgramiv(m_iID, GL_LINK_STATUS, &iSuccess);

		if (!iSuccess)
		{
			const int iBuffSize = 1024;
			GLchar strInfoLog[iBuffSize];
			glGetShaderInfoLog(m_iID, iBuffSize, nullptr, strInfoLog);
			std::cerr << "ERROR::SHADER: Link time error:\n" << strInfoLog << std::endl;
			m_bIsCompiled = false;
		}
		else
		{
			m_bIsCompiled = true;
		}

		glDeleteShader(iVertexShaderID);
		glDeleteShader(iFragmentShaderID);
	}

	CShaderProgram::~CShaderProgram()
	{
		glDeleteProgram(m_iID); // �������� ��������� ���������
	}

	bool CShaderProgram::createShader(const std::string& strSource, const GLenum eShaderType,
		GLuint& iShaderID)
	{
		iShaderID = glCreateShader(eShaderType);// id �������
		const char* strCode = strSource.c_str(); // ��������� ��� ������� � c-style ������
		glShaderSource(iShaderID, 1, &strCode, nullptr); // �������� �������� ��� �������
		glCompileShader(iShaderID);// ���������� �������

		// �������� ���������� ��������� ���������
		GLint iSuccess;
		glGetShaderiv(iShaderID, GL_COMPILE_STATUS, &iSuccess);

		if (!iSuccess)
		{
			const int iBuffSize = 1024;
			GLchar strInfoLog[iBuffSize];
			glGetShaderInfoLog(iShaderID, iBuffSize, nullptr, strInfoLog);
			std::cerr << "ERROR::SHADER: Compile time error:\n" << strInfoLog << std::endl;
			return false;
		}

		return true;
	}


	void CShaderProgram::use() const
	{
		glUseProgram(m_iID);
	}



	CShaderProgram& CShaderProgram::operator=(CShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(m_iID);

		this->m_iID = shaderProgram.m_iID;
		this->m_bIsCompiled = shaderProgram.m_bIsCompiled;

		shaderProgram.m_iID = 0;
		shaderProgram.m_bIsCompiled = false;

		return *this;
	}

	CShaderProgram::CShaderProgram(CShaderProgram&& shaderProgram) noexcept
	{
		this->m_iID = shaderProgram.m_iID;
		this->m_bIsCompiled = shaderProgram.m_bIsCompiled;

		shaderProgram.m_iID = 0;
		shaderProgram.m_bIsCompiled = false;
	}

	void CShaderProgram::setInt(const std::string& strName, const GLint iValue)
	{
		glUniform1i(glGetUniformLocation(m_iID, strName.c_str()), iValue);
	}

	void CShaderProgram::setMatrix4(const std::string& strName, const glm::mat4& matrix)
	{		
		glUniformMatrix4fv(glGetUniformLocation(m_iID, strName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}


}