#include "quad.hpp"


Quad::Quad(const GLfloat* vertices) {
	if (!vertices) return;

	glGenVertexArrays(1, &vertexArrayObject);
	if (!vertexArrayObject) return;

	initVertexBuffer(vertices);
	initElementBuffer();
	initTexCoordBuffer();
}


void Quad::draw() {
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Quad::initVertexBuffer(const GLfloat* vertices) {
	if (vertices == nullptr) return;

	glBindVertexArray(vertexArrayObject);
	glGenBuffers(1, &vertexBuffer);

	if (!vertexBuffer) return;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * vertSize,
		vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Quad::initElementBuffer() {
	glBindVertexArray(vertexArrayObject);
	glGenBuffers(1, &elementBuffer);

	if (!elementBuffer) return;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6,
		indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Quad::initTexCoordBuffer() {
	glBindVertexArray(vertexArrayObject);
	glGenBuffers(1, &texCoordBuffer);

	if (!texCoordBuffer) return;

	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * vertSize,
		texCoords, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


