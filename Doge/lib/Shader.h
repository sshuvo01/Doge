#ifndef _DOGE_SHADER_H_
#define _DOGE_SHADER_H_
#include "Core.h"
#include <glm/matrix.hpp>

namespace doge
{
	class Shader
	{
	public:
		NOCOPYNOASSIGN(Shader);
		Shader() = delete;
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, int value) const;
		void SetUniform1f(const std::string& name, float value) const;
		void SetUniform2f(const std::string& name, const glm::vec2& vec) const;
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
		void SetUniform4f(const std::string& name, const glm::vec4& vec) const;
		void SetUniform3f(const std::string& name, const glm::vec3& vec) const;
		void SetUniformMatrix4f(const std::string& name, const glm::mat4& matrix) const;

	private:
		uint m_RendererID;
		/* private functions */
		const std::string ReadShader(const std::string& filepath) const;
		uint CompileShader(uint type, const std::string& source) const;
		uint CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const;
		const std::string TypeToString(uint type) const;
		int GetUniformLocation(const std::string& uniformname) const;
	};
}

#endif // !_DOGE_SHADER_H_

