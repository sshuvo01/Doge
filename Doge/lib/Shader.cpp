#include "Shader.h"
#include <fstream>
#include <sstream>

namespace doge
{
	Shader::Shader(const std::string & vertexPath, const std::string & fragmentPath)
	{
		spdlog::debug("Constructing shader with {}, {}", vertexPath, fragmentPath);

		std::string vertexSource = ReadShader(vertexPath);
		std::string fragmentSource = ReadShader(fragmentPath);
		m_RendererID = CreateShader(vertexSource, fragmentSource);
	}

	Shader::~Shader()
	{
		GLCALL(glDeleteProgram(m_RendererID));
	}

	void Shader::Bind() const
	{
		GLCALL(glUseProgram(m_RendererID));
	}

	void Shader::Unbind() const
	{
		GLCALL(glUseProgram(0));
	}

	void Shader::SetUniform1i(const std::string & name, int value) const
	{
		Bind();
		int loc = GetUniformLocation(name);
		if (loc == -1) return;

		GLCALL(glUniform1i(loc, value));
	}

	void Shader::SetUniformTexture(const std::string& name, int value) const
	{
		SetUniform1i(name, value);
	}

	void Shader::SetUniform1f(const std::string & name, float value) const
	{
		Bind();
		int loc = GetUniformLocation(name);
		if (loc == -1) return;

		GLCALL(glUniform1f(loc, value));
	}

	void Shader::SetUniform2f(const std::string & name, const glm::vec2 & vec) const
	{
		Bind();
		int loc = GetUniformLocation(name);
		if (loc == -1) return;

		GLCALL(glUniform2f(loc, vec.x, vec.y));
	}

	void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3) const
	{
		Bind();
		int loc = GetUniformLocation(name);
		if (loc == -1) return;

		GLCALL(glUniform4f(loc, v0, v1, v2, v3));
	}

	void Shader::SetUniform4f(const std::string & name, const glm::vec4 & vec) const
	{
		Bind();
		int loc = GetUniformLocation(name);
		if (loc == -1) return;

		GLCALL(glUniform4f(loc, vec[0], vec[1], vec[2], vec[3]));
	}

	void Shader::SetUniform3f(const std::string & name, const glm::vec3 & vec) const
	{
		Bind();
		int loc = GetUniformLocation(name);
		if (loc == -1) return;

		GLCALL(glUniform3f(loc, vec[0], vec[1], vec[2]));
	}

	void Shader::SetUniformMatrix4f(const std::string & name, const glm::mat4 & matrix) const
	{
		Bind();
		int loc = GetUniformLocation(name);
		if (loc == -1) return;

		GLCALL(glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]));
	}

	const std::string Shader::ReadShader(const std::string & filepath) const
	{
		std::ifstream stream(filepath);

		if (!stream.is_open())
		{
			spdlog::error("Failed to open {}", filepath);
		}

		std::string line;
		std::stringstream theShader;

		spdlog::debug("Reading shader from {}", filepath);
		while (getline(stream, line))
		{
			theShader << line << '\n';
		}
		spdlog::debug("Read shader from {}", filepath);
		return theShader.str();
	}

	const std::string Shader::TypeToString(uint type) const
	{
		switch (type)
		{
		case GL_VERTEX_SHADER:
			return "VERTEX";
		case GL_FRAGMENT_SHADER:
			return "FRAGMENT";
		case GL_GEOMETRY_SHADER:
			return "GEOMETRY";
		default:
			return "UNKNOWN";
		}
		return "UNKNOWN";
	}

	int Shader::GetUniformLocation(const std::string & uniformname) const
	{
		GLCALL(int location = glGetUniformLocation(m_RendererID, uniformname.c_str()));
		if (location == -1)
		{
			spdlog::warn("{} not found in the shader", uniformname);
		}
		return location;
	}

	uint Shader::CompileShader(uint type, const std::string& source) const
	{
		uint id = glCreateShader(type);
		const char* src = source.c_str();
		GLCALL(glShaderSource(id, 1, &src, nullptr));
		GLCALL(glCompileShader(id));

		int result;
		GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE)
		{
			int length;
			GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length * sizeof(char));

			GLCALL(glGetShaderInfoLog(id, length, &length, message));

			//std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "VERTEX " : "FRAGMENT ");
			//std::cout << message << std::endl;
			spdlog::critical("Failed to comile {} shader: {}", TypeToString(type), message);
			GLCALL(glDeleteShader(id));
			return 0;
		}

		return id;
	}

	uint Shader::CreateShader(const std::string & vertexShader, const std::string & fragmentShader) const
	{
		uint program = glCreateProgram();
		uint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		uint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		GLCALL(glAttachShader(program, vs));
		GLCALL(glAttachShader(program, fs));

		GLCALL(glLinkProgram(program));
		GLCALL(glValidateProgram(program));

		GLCALL(glDeleteShader(fs));
		GLCALL(glDeleteShader(vs));

		return program;
	}
}