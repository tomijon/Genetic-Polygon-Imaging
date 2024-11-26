#include "Solution.hpp"






Solution::Solution(SolutionSettings settings) {
	numVertices = settings.MAX_VERTICES;

	glGenVertexArrays(1, &vertexArrayObject);
	if (!vertexArrayObject) return;

	glBindVertexArray(vertexArrayObject);
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &colorBuffer);
	if (!vertexBuffer || !colorBuffer) return;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glNamedBufferStorage(
		vertexBuffer,
		sizeof(uint32_t) * numVertices * 2,
		vertexInformation,
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT
	);
	glVertexAttribIPointer(0, 2, GL_INT, 
		sizeof(uint32_t) * 2, nullptr);
	glEnableVertexAttribArray(0);
	void* vertPtr = glMapNamedBuffer(vertexBuffer, GL_WRITE_ONLY);
	if (!vertPtr) return;
	vertexInformation = static_cast<uint32_t*>(vertPtr);

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glNamedBufferStorage(
		colorBuffer,
		sizeof(uint32_t) * numVertices * 4,
		colorInformation,
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT
	);
	glVertexAttribIPointer(1, 4, GL_INT, 
		sizeof(uint32_t) * 4, nullptr);
	glEnableVertexAttribArray(1);
	void* colorPtr = glMapNamedBuffer(colorBuffer, GL_WRITE_ONLY);
	if (!colorPtr) return;
	colorInformation = static_cast<uint32_t*>(colorPtr);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	state = SolutionState::VALID;
}


Solution::~Solution() {
	delete[] vertexInformation;
	delete[] colorInformation;

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteVertexArrays(1, &vertexArrayObject);
}


void Solution::flushBuffers() {
	glFlushMappedNamedBufferRange(vertexBuffer, 0,
		sizeof(uint32_t) * 2 * numVertices);

	glFlushMappedNamedBufferRange(colorBuffer, 0,
		sizeof(uint32_t) * 4 * numVertices);
}


void Solution::bind() {
	glBindVertexArray(vertexArrayObject);
}


void Solution::draw() {
	vertexInformation[0] = 0;
	vertexInformation[1] = 0;
	vertexInformation[2] = 0;
	vertexInformation[3] = 0.5;
	vertexInformation[4] = 0.5;
	vertexInformation[5] = 0.5;
	colorInformation[0] = 255;
	colorInformation[1] = 255;
	colorInformation[2] = 255;
	colorInformation[3] = 255;
	colorInformation[4] = 255;
	colorInformation[5] = 255;
	colorInformation[6] = 255;
	colorInformation[7] = 255;
	bind();
	//flushBuffers();
	glDrawArrays(GL_LINES, 0, 10);
}
