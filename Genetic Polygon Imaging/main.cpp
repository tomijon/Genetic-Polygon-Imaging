#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Renderer.hpp"
#include "Window.hpp"
#include "ErrorCodes.hpp"
#include "Shader.hpp"
#include "Solution.hpp"
#include "quad.hpp"
#include "ImageHandler.hpp"



void APIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar * message, const void* userParam) {
	std::cerr << "OpenGL Debug Message: " << message << std::endl;
}

int main(int argc, char* argv[]) {
	Window window(400, 200, false);

	if (!window.isInitialised()) {
		std::cerr << "Failed to initialise window." << std::endl;
		return ErrorCode::WINDOW_CREATION;
	}

	Shader solutionShader("solution_vertex.glsl", "solution_fragment.glsl");
	if (!solutionShader.isInitialised()) {
		std::cerr << "Failed to create solution shader program." << std::endl;
		return ErrorCode::SHADER_CREATION;
	}

	Shader textureShader("drawtex_vertex.glsl", "drawtex_fragment.glsl");
	if (!textureShader.isInitialised()) {
		std::cerr << "Failed to create texture shader program." << std::endl;
		return ErrorCode::SHADER_CREATION;
	}

	Renderer renderer;
	if (!renderer.isInitialised()) {
		std::cerr << "Failed to create renderer." << std::endl;
		return ErrorCode::RENDERER_CREATION;
	}

	GLuint targetImage = ImageHandler::load_image_as_texture("darwin.png");
	if (!targetImage) {
		std::cerr << "Failed to load target image." << std::endl;
		return ErrorCode::TARGET_LOADING;
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
		0.1,
		200,
		200
	);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFF);

	glDebugMessageCallback(MessageCallback, nullptr);

	Solution test(settings);
	if (glGetError() != GL_NO_ERROR) {
		std::cerr << "OpenGL Error: " << glGetError() << std::endl;
	}
	if (test.getState() == SolutionState::INVALID) {
		std::cerr << "Failed to create solution." << std::endl;
		return ErrorCode::SOLUTION_CREATION;
	}

	GLfloat evalVertices[8] = {0, -1, 1, -1, 0, 1, 1, 1};
	GLfloat targetVertices[8] = {-1, -1, 0, -1, -1, 1, 0, 1};
	Quad evaluated = Quad(&evalVertices[0]);
	Quad target = Quad(&targetVertices[0]);

	glClearColor(0, 0, 0, 1);
	glUseProgram(solutionShader.getProgram());

	glUniform1f(glGetUniformLocation(solutionShader.getProgram(), "width"),
		static_cast<float>(settings.WIDTH));
	glUniform1f(glGetUniformLocation(solutionShader.getProgram(), "height"),
		static_cast<float>(settings.HEIGHT));


	while (window.isOpen()) {
		glfwPollEvents();
		window.update();
		if (!window.isOpen()) continue;

		glUseProgram(solutionShader.getProgram());
		test.draw();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, window.getWidth(), window.getHeight());
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(textureShader.getProgram());
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(
			textureShader.getProgram(), "drawTex"), 0);

		glBindTexture(GL_TEXTURE_2D, targetImage);
		target.draw();
				
		glBindTexture(GL_TEXTURE_2D, test.getResultImage());
		evaluated.draw();
		glBindTexture(GL_TEXTURE_2D, 0);



		

		if (glGetError() != GL_NO_ERROR) {
			std::cerr << "OpenGL Error: " << glGetError() << std::endl;
		}
	}
	return ErrorCode::SUCCESS;
}