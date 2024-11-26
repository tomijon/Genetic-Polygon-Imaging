#include "Solution.hpp"






Solution::Solution(SolutionSettings settings) {
	numVertices = settings.MAX_VERTICES;

	vertexInformation = new uint32_t[numVertices * 2];	// 2 for x and y.
	colorInformation = new uint32_t[numVertices * 4];	// 4 for rgba.

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
		sizeof(uint32_t) * 6, nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glNamedBufferStorage(
		colorBuffer,
		sizeof(uint32_t) * numVertices * 4,
		colorInformation,
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT
	);
	glVertexAttribIPointer(1, 4, GL_INT, 
		sizeof(uint32_t) * 6, nullptr);
	glEnableVertexAttribArray(1);

	state = SolutionState::VALID;

	
}


Solution::~Solution() {
	delete[] vertexInformation;
	delete[] colorInformation;
}


GLuint Solution::createVertexArrayObject() {
	glCreateVertexArrays(1, &vertexArrayObject);


}


GLuint Solution::createBuffer() {
	GLuint buffer;
	glCreateBuffers(1, &buffer);
	return buffer;
}
