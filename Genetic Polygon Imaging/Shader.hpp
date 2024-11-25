#pragma once

#include <string>
#include <filesystem>

#include "glad/glad.h"

namespace ShaderConfig {
	constexpr int BUFFER_SIZE = 1024;
}


class Shader {
public:
	Shader() {};
	Shader(const std::string& vertex, const std::string& fragment);
	Shader(const std::string& compute);

	Shader(const Shader& other) noexcept : m_programID(other.m_programID), m_initialised(other.m_initialised) {}
	Shader(Shader&& other) noexcept : m_programID(other.m_programID), m_initialised(other.m_initialised) {
		other.m_programID = 0;
		other.m_initialised = false;
	}

	~Shader();

	inline GLuint getProgram() const { return m_programID; }
	inline bool isInitialised() const { return m_initialised; }

	Shader& operator=(const Shader& other) noexcept {
		m_programID = other.m_programID;
		m_initialised = other.m_initialised;
		return *this;
	}

	Shader& operator=(Shader&& other) noexcept {
		m_programID = other.m_programID;
		m_initialised = other.m_initialised;
		other.m_programID = 0;
		other.m_initialised = false;
		return *this;
	}

private:
	static bool compileShader(GLuint shader, const std::filesystem::path& path);
	static bool linkProgram(GLuint program);

	static GLuint createShaderProgram(GLuint vertex, GLuint fragment);
	static GLuint createShader(const std::string& filename, const GLenum type);

	GLuint m_programID = 0;
	bool m_initialised = false;	
};

