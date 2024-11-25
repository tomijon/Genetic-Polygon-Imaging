#include <iostream>
#include <fstream>

#include "Shader.hpp"



Shader::Shader(const std::string& vertex, const std::string& fragment) {
	GLuint vertexShader = Shader::createShader(vertex, GL_VERTEX_SHADER);
	if (!vertexShader) return;

	GLuint fragmentShader = Shader::createShader(fragment, GL_FRAGMENT_SHADER);
	if (!fragmentShader) {
		glDeleteShader(vertexShader);
		return;
	}

	m_programID = Shader::createShaderProgram(vertexShader, fragmentShader);

	if (!m_programID) return;
	m_initialised = true;
}


Shader::Shader(const std::string& compute) {
	GLuint computeShader = Shader::createShader(compute, GL_COMPUTE_SHADER);
	if (!computeShader) return;

	GLuint program = glCreateProgram();
	if (!program) return;

	glAttachShader(program, computeShader);
	bool success = Shader::linkProgram(program);

	if (!success) {
		int length;
		char buffer[ShaderConfig::BUFFER_SIZE];
		glGetProgramInfoLog(m_programID, ShaderConfig::BUFFER_SIZE, &length, buffer);
		std::cerr << buffer << std::endl;
		return;
	}

	m_programID = program;
	m_initialised = true;
}


Shader::~Shader() {
	if (m_programID) glDeleteProgram(m_programID);
}


GLuint Shader::createShader(const std::string& filename, const GLenum type) {
	GLuint shader = glCreateShader(type);
	if (!shader) return 0;

	if (compileShader(shader, filename)) return shader;

	int length;
	char buffer[ShaderConfig::BUFFER_SIZE];

	glGetShaderInfoLog(shader, ShaderConfig::BUFFER_SIZE, &length, buffer);
	std::cerr << buffer << std::endl;

	return 0;
}


bool Shader::compileShader(GLuint shader, const std::filesystem::path& path) {
	std::ifstream file(path);

	if (file.is_open()) {
		std::stringstream sourceStream;
		sourceStream << file.rdbuf();
		file.close();
		
		std::string sourceString = sourceStream.str();
		const char* source = sourceString.c_str();

		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);

		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		return static_cast<bool>(success);
	}
	return false;
}


GLuint Shader::createShaderProgram(GLuint vertex, GLuint fragment) {
	GLuint program = glCreateProgram();

	if (!program) return 0;

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	
	bool success = Shader::linkProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	if (success) return program;

	int length;
	char buffer[ShaderConfig::BUFFER_SIZE];
	glGetProgramInfoLog(program, ShaderConfig::BUFFER_SIZE, &length, buffer);
	std::cerr << buffer << std::endl;
	return 0;
}


bool Shader::linkProgram(GLuint program) { 
	glLinkProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	return static_cast<bool>(success);
}