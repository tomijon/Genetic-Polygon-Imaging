#pragma once
#include "glad/glad.h"


class Quad {
public:
	Quad(const GLfloat* vertices);
	~Quad() { delete vertices; }

	void draw();

	void initVertexBuffer(const GLfloat* vertices);
	void initElementBuffer();
	void initTexCoordBuffer();

private:
	GLuint vertexArrayObject	= 0;
	GLuint vertexBuffer			= 0;
	GLuint elementBuffer		= 0;
	GLuint texCoordBuffer		= 0;

	GLfloat *vertices = nullptr;

	const GLuint indices[6] = { 0, 1, 2, 1, 2, 3 };
	const GLfloat texCoords[8] = { 0, 1, 1, 1, 0, 0, 1, 0 };
	const int numVertices = 4;
	const int vertSize = 2;
};
