#pragma once

#include <shader\shader.h>

namespace tulip {

	class OpenGLShader : public Shader{
	public:
		OpenGLShader();
		~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void readFile(const std::string& path) override;
		virtual void setSource(const std::string& src) override;
		virtual void compile() override;


		/* UNIFORMS */
		virtual void setInt(const std::string& name, int32_t val);
		virtual void setInt2(const std::string& name, const glm::ivec2& val);
		virtual void setInt3(const std::string& name, const glm::ivec3& val);
		virtual void setInt4(const std::string& name, const glm::ivec4& val);

		//FLOAT
		virtual void setFloat(const std::string& name, float val);
		virtual void setFloat2(const std::string& name, const glm::vec2& val);
		virtual void setFloat3(const std::string& name, const glm::vec3& val);
		virtual void setFloat4(const std::string& name, const glm::vec4& val);

		//MAT2
		virtual void setMat2(const std::string& name, const glm::mat2& mat);
		virtual void setMat2x3(const std::string& name, const glm::mat2x3& mat);
		virtual void setMat2x4(const std::string& name, const glm::mat2x4& mat);

		//MAT3
		virtual void setMat3(const std::string& name, const glm::mat3& mat);
		virtual void setMat3x2(const std::string& name, const glm::mat3x2& mat);
		virtual void setMat3x4(const std::string& name, const glm::mat3x4& mat);

		//MAT4
		virtual void setMat4(const std::string& name, const glm::mat4& mat);
		virtual void setMat4x2(const std::string& name, const glm::mat4x2& mat);
		virtual void setMat4x3(const std::string& name, const glm::mat4x3& mat);


	private:

		uint32_t m_id;

		uint32_t m_vertexID;
		uint32_t m_tessControlID;
		uint32_t m_tessEvalID;
		uint32_t m_geometryID;
		uint32_t m_fragmentID;

		std::string m_vertexSource;
		std::string m_tessControlSource;
		std::string m_tessEvalSource;
		std::string m_geometrySource;
		std::string m_fragmentSource;

	};

}