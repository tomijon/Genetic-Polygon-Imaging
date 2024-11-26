#include <iostream>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Renderer.hpp"
#include "Window.hpp"
#include "ErrorCodes.hpp"
#include "Shader.hpp"
#include "Solution.hpp"


void APIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar * message, const void* userParam) {
	std::cerr << "OpenGL Debug Message: " << message << std::endl;
}

int main(int argc, char* argv[]) {
	Window window(1280, 720);

	

	if (!window.isInitialised()) {
		std::cerr << "Failed to initialise window." << std::endl;
		return ErrorCode::WINDOW_CREATION;
	}

	Shader screenSpace("vertex.glsl", "fragment.glsl");
	if (!screenSpace.isInitialised()) {
		std::cerr << "Failed to create shader program." << std::endl;
		return ErrorCode::SHADER_CREATION;
	}

	Renderer renderer;
	if (!renderer.isInitialised()) {
		std::cerr << "Failed to create renderer." << std::endl;
		return ErrorCode::RENDERER_CREATION;
	}

	SolutionSettings settings(
		100,
		5,
		16,
		20,
		235,
		5,
		5,
		5,
		0.1,
		0.1
	);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, nullptr);

	Solution test(settings);
	if (glGetError() != GL_NO_ERROR) {
		std::cerr << "OpenGL Error: " << glGetError() << std::endl;
	}
	if (test.getState() == SolutionState::INVALID) {
		std::cerr << "Failed to create solution." << std::endl;
		return ErrorCode::SOLUTION_CREATION;
	}


	glClearColor(0, 0, 0, 1);


	while (window.isOpen()) {
		glfwPollEvents();
		window.update();
		if (!window.isOpen()) continue;

		glClear(GL_COLOR_BUFFER_BIT);
		test.draw();

		if (glGetError() != GL_NO_ERROR) {
			std::cerr << "OpenGL Error: " << glGetError() << std::endl;
		}
	}
	return ErrorCode::SUCCESS;
}