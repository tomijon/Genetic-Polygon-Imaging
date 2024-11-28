#define _CRT_SECURE_NO_WARNINGS

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"
#include "ImageHandler.hpp"

GLuint ImageHandler::load_image_as_texture(const std::string& name) {
	std::filesystem::path file(name);
	if (!std::filesystem::exists(name)) return 0;

	int width, height, channels;
	unsigned char* data = stbi_load(
		file.string().c_str(), &width, &height, &channels, 0
	);

	GLuint texture;
	glGenTextures(1, &texture);
	if (!texture) return 0;

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	return texture;
}
