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
	void* vertPtr = glMapNamedBufferRange(vertexBuffer, 0, sizeof(uint32_t) * 2 * numVertices,
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT |GL_MAP_FLUSH_EXPLICIT_BIT);
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
	void* colorPtr = glMapNamedBufferRange(colorBuffer, 0, sizeof(uint32_t) * 4 * numVertices,
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT |GL_MAP_FLUSH_EXPLICIT_BIT);
	if (!colorPtr) return;
	colorInformation = static_cast<uint32_t*>(colorPtr);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	state = SolutionState::VALID;
}


Solution::~Solution() {
	glUnmapNamedBuffer(vertexBuffer);
	glUnmapNamedBuffer(colorBuffer);

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


void Solution::draw() {
	for (int i = 0; i < numVertices; i++) {
		int vertIndex = (i * 2);
		int colorIndex = (i * 4);

		vertexInformation[vertIndex + 0] = rand() % 1280;
		vertexInformation[vertIndex + 1] = rand() % 720;

		colorInformation[colorIndex + 0] = rand() % 255;
		colorInformation[colorIndex + 1] = rand() % 255;
		colorInformation[colorIndex + 2] = rand() % 255;
		colorInformation[colorIndex + 3] = 255;
	}


	glBindVertexArray(vertexArrayObject);

	flushBuffers();
	glDrawArrays(GL_TRIANGLES, 0, 553);

	glBindVertexArray(0);
}
