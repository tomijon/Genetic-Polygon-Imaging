#include "Solution.hpp"

#include <iostream>





Solution::Solution(SolutionSettings settings) :
	verticesPerPolygon(settings.MAX_VERTICES),
	maxPolygons(settings.MAX_POLYGONS),
	numVertices(settings.MAX_VERTICES * settings.MAX_POLYGONS),
	width(settings.WIDTH),
	height(settings.HEIGHT)
{
	glGenVertexArrays(1, &vertexArrayObject);
	if (!vertexArrayObject) return;

	glBindVertexArray(vertexArrayObject);

	initVertexBuffer();
	if (!vertexBuffer) return;

	initColorBuffer();
	if (!colorBuffer) return;

	initDrawTexture();
	if (!drawTexture) return;

	initFramebuffer();
	if (!framebuffer) return;

	state = SolutionState::VALID;
}


Solution::~Solution() {
	glUnmapNamedBuffer(vertexBuffer);
	glUnmapNamedBuffer(colorBuffer);
	glUnmapNamedBuffer(elementBuffer);
	glUnmapNamedBuffer(evalBuffer);

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteBuffers(1, &elementBuffer);
	glDeleteBuffers(1, &evalBuffer);

	glDeleteTextures(1, &drawTexture);
	glDeleteFramebuffers(1, &framebuffer);

	glDeleteVertexArrays(1, &vertexArrayObject);
}


void Solution::initVertexBuffer() {
	glBindVertexArray(vertexArrayObject);
	glGenBuffers(1, &vertexBuffer);
	if (!vertexBuffer) return;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	unsigned int itemSize = 2;
	GLsizeiptr bufSize = sizeof(GLuint) * numVertices * itemSize;

	glBufferStorage(
		GL_ARRAY_BUFFER, bufSize, nullptr,
		GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT |	GL_MAP_PERSISTENT_BIT
	);
	void* ptr = glMapBufferRange(
		GL_ARRAY_BUFFER, 0, bufSize,
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_FLUSH_EXPLICIT_BIT
	);
	vertexInformation = static_cast<GLuint*>(ptr);

	glVertexAttribIPointer(0, itemSize, GL_UNSIGNED_INT, 0, nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Solution::initColorBuffer() {
	glBindVertexArray(vertexArrayObject);
	glGenBuffers(1, &colorBuffer);
	if (!colorBuffer) return;

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);

	unsigned int itemSize = 4;
	GLsizeiptr bufSize = sizeof(GLuint) * numVertices * itemSize;

	glBufferStorage(
		GL_ARRAY_BUFFER, bufSize, nullptr,
		GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT |	GL_MAP_PERSISTENT_BIT
	);
	void* ptr = glMapBufferRange(
		GL_ARRAY_BUFFER, 0, bufSize,
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_FLUSH_EXPLICIT_BIT
	);
	colorInformation = static_cast<GLuint*>(ptr);

	glVertexAttribIPointer(1, itemSize, GL_UNSIGNED_INT, 0, nullptr);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Solution::initFramebuffer() {
	glGenFramebuffers(1, &framebuffer);
	if (!framebuffer) return;

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, drawTexture);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, drawTexture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		framebuffer = 0;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Solution::initDrawTexture() {
	glGenTextures(1, &drawTexture);
	if (!drawTexture) return;

	glBindTexture(GL_TEXTURE_2D, drawTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Solution::mapGenes() {
	vertexGenes = new Gene[maxPolygons];
	colorGenes = new Gene[maxPolygons];

	int currentPolygon = 0;
	for (int i = 0; i < maxPolygons; i++) {
		currentPolygon = i * verticesPerPolygon;
		Gene vertexGene(verticesPerPolygon * 2, &vertexInformation[currentPolygon * 2]);
		Gene colorGene(verticesPerPolygon * 4, &colorInformation[currentPolygon * 4]);

		vertexGenes[i] = vertexGene;
		colorGenes[i] = colorGene;
	}
}


void Solution::flushBuffers() {
	glFlushMappedNamedBufferRange(vertexBuffer, 0,
		sizeof(GLuint) * 2 * numVertices);

	glFlushMappedNamedBufferRange(colorBuffer, 0,
		sizeof(GLuint) * 4 * numVertices);
}


void Solution::draw() {
	for (int i = 0; i < numVertices; i++) {
		int vertIndex = (i * 2);
		int colorIndex = (i * 4);

		vertexInformation[vertIndex + 0] = rand() % width;
		vertexInformation[vertIndex + 1] = rand() % height;

		colorInformation[colorIndex + 0] = rand() % 255;
		colorInformation[colorIndex + 1] = rand() % 255;
		colorInformation[colorIndex + 2] = rand() % 255;
		colorInformation[colorIndex + 3] = 255;
	}

	glBindVertexArray(vertexArrayObject);

	flushBuffers();
	glDrawArrays(GL_TRIANGLES, 0, 30);

	glBindVertexArray(0);
}
