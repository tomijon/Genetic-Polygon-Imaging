#include "Solution.hpp"






Solution::Solution(SolutionSettings settings) {
	numVertices = settings.MAX_VERTICES;

}


GLuint Solution::createVertexArrayObject() {
	glCreateVertexArrays(1, &vertexArrayObject);


}


void Solution::createVertexBuffer() {
	glCreateBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
}
