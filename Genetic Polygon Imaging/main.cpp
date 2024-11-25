#include <iostream>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Renderer.hpp"
#include "Window.hpp"
#include "ErrorCodes.hpp"
#include "Shader.hpp"


int main(int argc, char* argv[]) {
	Window window(1920, 1080);

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

	while (window.isOpen()) {
		glfwPollEvents();
		window.update();
		if (!window.isOpen()) continue;




	}

	return ErrorCode::SUCCESS;
}