#pragma once

#include <string>
#include <filesystem>

#include "glad/glad.h"

class ImageHandler {
public:
	ImageHandler() {};
	~ImageHandler() {};

	static GLuint load_image_as_texture(const std::string& name);
	static GLuint save_texture(GLuint texture) {};
};

