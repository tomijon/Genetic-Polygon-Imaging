


#include "Renderer.hpp"


Renderer::Renderer() {
	glEnable(GL_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	instance = this;
	initialised = true;
};

Renderer::~Renderer() {};
