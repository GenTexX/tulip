#include "tulippch.h"
#include "openGLShader.h"

#include <logging\logger.h>

#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\type_ptr.hpp>

#define MAX_CHARACTERS_PER_LINE 1024

namespace tulip {

	OpenGLShader::OpenGLShader() {

	}

	OpenGLShader::~OpenGLShader() {
	}

	void OpenGLShader::bind() const {
		glUseProgram(this->m_id);
	}

	void OpenGLShader::unbind() const {
		glUseProgram(NULL);
	}

	void OpenGLShader::readFile(const std::string& path) {
		FILE* shaderFile = fopen(path.c_str(), "r");

		if (!shaderFile) {
			TULIP_CORE_ERROR("ERROR: File {} does not exist!", path);
			return;
		}

		std::stringstream vertex;
		std::stringstream tessControl;
		std::stringstream tessEval;
		std::stringstream geometry;
		std::stringstream fragment;

		char line[MAX_CHARACTERS_PER_LINE];
		enum ShaderReadMode { NONE = 0, VERTEX = 1, TESSCONTROL = 2, TESSEVAL = 3, GEOMETRY = 4, FRAGMENT = 5 };
		ShaderReadMode mode = ShaderReadMode::NONE;
		while (fgets(line, MAX_CHARACTERS_PER_LINE, shaderFile) != NULL) {

			std::string string_line = line;

			if (string_line.find("#shader") != std::string::npos) {
				if (string_line.find("vertex") != std::string::npos)
					mode = ShaderReadMode::VERTEX;
				else if (string_line.find("control") != std::string::npos)
					mode = ShaderReadMode::TESSCONTROL;
				else if (string_line.find("evaluation") != std::string::npos)
					mode = ShaderReadMode::TESSEVAL;
				else if (string_line.find("geometry") != std::string::npos)
					mode = ShaderReadMode::GEOMETRY;
				else if (string_line.find("fragment") != std::string::npos)
					mode = ShaderReadMode::FRAGMENT;
				continue;
			}

			switch (mode)
			{
			case NONE:
				break;
			case VERTEX:
				vertex << line << std::endl;
				break;
			case TESSCONTROL:
				tessControl << line << std::endl;
				break;
			case TESSEVAL:
				tessEval << line << std::endl;
				break;
			case GEOMETRY:
				geometry << line << std::endl;
				break;
			case FRAGMENT:
				fragment << line << std::endl;
				break;
			default:
				break;
			}

		}

		fclose(shaderFile);

		this->m_vertexSource = vertex.str();
		this->m_tessControlSource = tessControl.str();
		this->m_tessEvalSource = tessEval.str();
		this->m_geometrySource = geometry.str();
		this->m_fragmentSource = fragment.str();
	}

	void OpenGLShader::setSource(const std::string& src) {
		std::istringstream srcStream(src);
		std::string line;

		std::stringstream vertex;
		std::stringstream tessControl;
		std::stringstream tessEval;
		std::stringstream geometry;
		std::stringstream fragment;

		enum ShaderReadMode { NONE = 0, VERTEX = 1, TESSCONTROL = 2, TESSEVAL = 3, GEOMETRY = 4, FRAGMENT = 5 };
		ShaderReadMode mode = ShaderReadMode::NONE;

		while (std::getline(srcStream, line)) {

			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos)
					mode = ShaderReadMode::VERTEX;
				else if (line.find("control") != std::string::npos)
					mode = ShaderReadMode::TESSCONTROL;
				else if (line.find("evaluation") != std::string::npos)
					mode = ShaderReadMode::TESSEVAL;
				else if (line.find("geometry") != std::string::npos)
					mode = ShaderReadMode::GEOMETRY;
				else if (line.find("fragment") != std::string::npos)
					mode = ShaderReadMode::FRAGMENT;
				continue;
			}

			switch (mode)
			{
			case NONE:
				break;
			case VERTEX:
				vertex << line << std::endl;
				break;
			case TESSCONTROL:
				tessControl << line << std::endl;
				break;
			case TESSEVAL:
				tessEval << line << std::endl;
				break;
			case GEOMETRY:
				geometry << line << std::endl;
				break;
			case FRAGMENT:
				fragment << line << std::endl;
				break;
			default:
				break;
			}
		}

		this->m_vertexSource = vertex.str();
		this->m_tessControlSource = tessControl.str();
		this->m_tessEvalSource = tessEval.str();
		this->m_geometrySource = geometry.str();
		this->m_fragmentSource = fragment.str();

	}

	void OpenGLShader::compile() {
		if (!this->m_vertexSource.empty()) this->m_vertexID = glCreateShader(GL_VERTEX_SHADER);
		if (!this->m_tessControlSource.empty()) this->m_tessControlID = glCreateShader(GL_TESS_CONTROL_SHADER);
		if (!this->m_tessEvalSource.empty()) this->m_tessEvalID = glCreateShader(GL_TESS_EVALUATION_SHADER);
		if (!this->m_geometrySource.empty()) this->m_geometryID = glCreateShader(GL_GEOMETRY_SHADER);
		if (!this->m_fragmentSource.empty()) this->m_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

		if (!this->m_vertexSource.empty() && this->m_vertexID) {
			const char* vertexShaderSource = this->m_vertexSource.c_str();
			glShaderSource(this->m_vertexID, 1, &vertexShaderSource, nullptr);
			glCompileShader(this->m_vertexID);

			int vertexCompilationResult;
			glGetShaderiv(this->m_vertexID, GL_COMPILE_STATUS, &vertexCompilationResult);
			if (vertexCompilationResult == GL_FALSE) {
				int length;
				glGetShaderiv(this->m_vertexID, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*)_malloca(length * sizeof(char));
				glGetShaderInfoLog(this->m_vertexID, length, &length, msg);

				TULIP_CORE_ERROR("ERROR: Failed to compile Vertex-Shader!");
				TULIP_CORE_ERROR(msg);
			}
		}

		if (!this->m_fragmentSource.empty() && this->m_fragmentID) {
			const char* fragmentShaderSource = this->m_fragmentSource.c_str();
			glShaderSource(this->m_fragmentID, 1, &fragmentShaderSource, nullptr);
			glCompileShader(this->m_fragmentID);

			int fragmentCompilationResult;
			glGetShaderiv(this->m_fragmentID, GL_COMPILE_STATUS, &fragmentCompilationResult);
			if (fragmentCompilationResult == GL_FALSE) {
				int length;
				glGetShaderiv(this->m_fragmentID, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*)_malloca(length * sizeof(char));
				glGetShaderInfoLog(this->m_fragmentID, length, &length, msg);

				TULIP_CORE_ERROR("ERROR: Failed to compile Fragment-Shader!");
				TULIP_CORE_ERROR(msg);
			}
		}

		this->m_id = glCreateProgram();
		glAttachShader(this->m_id, this->m_vertexID);
		glAttachShader(this->m_id, this->m_fragmentID);
		glLinkProgram(this->m_id);

		int length = 0;
		glGetProgramiv(this->m_id, GL_INFO_LOG_LENGTH, &length);

		if (length > 0) {
			char* msg = new char[length];
			glGetProgramInfoLog(this->m_id, length, NULL, msg);
			TULIP_CORE_ERROR("ERROR: Failed to link program!");
			TULIP_CORE_ERROR(msg);
			delete[] msg;
		}

		glDeleteShader(this->m_vertexID);
		glDeleteShader(this->m_fragmentID);
	}

	//INT
	void OpenGLShader::setInt(const std::string& name, int32_t val) {
		glUniform1i(glGetUniformLocation(this->m_id, name.c_str()), val);
	}

	void OpenGLShader::setInt2(const std::string& name, const glm::ivec2& val) {
		glUniform2i(glGetUniformLocation(this->m_id, name.c_str()), val.x, val.y);
	}

	void OpenGLShader::setInt3(const std::string& name, const glm::ivec3& val) {
		glUniform3i(glGetUniformLocation(this->m_id, name.c_str()), val.x, val.y, val.z);
	}

	void OpenGLShader::setInt4(const std::string& name, const glm::ivec4& val) {
		glUniform4i(glGetUniformLocation(this->m_id, name.c_str()), val.x, val.y, val.z, val.w);
	}

	//FLOAT
	void OpenGLShader::setFloat(const std::string& name, float val) {
		glUniform1f(glGetUniformLocation(this->m_id, name.c_str()), val);
	}

	void OpenGLShader::setFloat2(const std::string& name, const glm::vec2& val) {
		glUniform2f(glGetUniformLocation(this->m_id, name.c_str()), val.x, val.y);
	}

	void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& val) {
		glUniform3f(glGetUniformLocation(this->m_id, name.c_str()), val.x, val.y, val.z);
	}

	void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& val) {
		glUniform4f(glGetUniformLocation(this->m_id, name.c_str()), val.x, val.y, val.z, val.w);
	}


	//MATRICES
	void OpenGLShader::setMat2(const std::string& name, const glm::mat2& mat) {
		glUniformMatrix2fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::setMat2x3(const std::string& name, const glm::mat2x3& mat) {
		glUniformMatrix2x3fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::setMat2x4(const std::string& name, const glm::mat2x4& mat) {
		glUniformMatrix2x4fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::setMat3(const std::string& name, const glm::mat3& mat) {
		glUniformMatrix3fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::setMat3x2(const std::string& name, const glm::mat3x2& mat) {
		glUniformMatrix3x2fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::setMat3x4(const std::string& name, const glm::mat3x4& mat) {
		glUniformMatrix3x4fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::setMat4(const std::string& name, const glm::mat4& mat) {
		glUniformMatrix4fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::setMat4x2(const std::string& name, const glm::mat4x2& mat) {
		glUniformMatrix4x2fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::setMat4x3(const std::string& name, const glm::mat4x3& mat) {
		glUniformMatrix4x3fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}
}