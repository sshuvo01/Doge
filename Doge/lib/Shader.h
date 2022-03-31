#ifndef _DOGE_SHADER_H_
#define _DOGE_SHADER_H_
#include "Core.h"
#include <glm/matrix.hpp>

namespace doge
{
	struct ShaderSpec
	{
		std::string modelMatName = "u_Model";
		std::string viewMatName = "u_View";
		std::string projectionMatName = "u_Projection";
		std::string mvpMatName = "u_MVP"; // model * view * projection
		std::string vpMatName = "u_VP"; // view * projection
		std::string diffuseMapName = "u_DiffuseMap";
		uint positionLoc = 0;
		uint normalLoc = 1;
		uint texCoordLoc = 2;
		uint instanceMatLoc = 5;
		uint materialMapCount = 5; // might change later
	};

	class Shader final
	{
	public:
		NOCOPYNOASSIGN(Shader);
		Shader() = delete;
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, int value) const;
		void SetUniformTexture(const std::string& name, int value) const;
		void SetUniform1f(const std::string& name, float value) const;
		void SetUniform2f(const std::string& name, const glm::vec2& vec) const;
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
		void SetUniform4f(const std::string& name, const glm::vec4& vec) const;
		void SetUniform3f(const std::string& name, const glm::vec3& vec) const;
		void SetUniformMatrix4f(const std::string& name, const glm::mat4& matrix) const;
		/*-----------*/
		inline const ShaderSpec& GetShaderSpec() const { return m_ShaderSpec; }
		inline void SetShaderSpec(const ShaderSpec& ss) { m_ShaderSpec = ss; }
		//
		static const std::string GetUniformName(const std::string& structVarName, uint index, const std::string& varName);
	private:
		uint m_RendererID;
		ShaderSpec m_ShaderSpec;
		/* private functions */
		const std::string ReadShader(const std::string& filepath) const;
		uint CompileShader(uint type, const std::string& source) const;
		uint CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const;
		const std::string TypeToString(uint type) const;
		int GetUniformLocation(const std::string& uniformname) const;
	};
}

#endif // !_DOGE_SHADER_H_

