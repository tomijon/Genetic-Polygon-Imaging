#pragma once

#include <mutex>
#include <thread>

#include "glad/glad.h"


struct SolutionSettings {
	SolutionSettings(const std::string& config);

	const int MAX_POLYGONS;
	const int RETRIES_BEFORE_NEW_POLYGON;
	const int MAX_VERTICES;
	const int MIN_ALPHA;
	const int MAX_ALPHA;

	const int SELECT_COUNT;
	const int CROSS_COUNT;
	const int START_COUNT;

	const float MUT_PB;
	const float CX_PB;
};


enum SolutionState {
	INVALID = 0,
	VALID = 1,
	EVALUATED = 2,
};


class Gene {
public:
	Gene(const int size) : information(new int[size]), length(size) {}
	Gene(const int size, int* data) : information(data), length(size) {}
	virtual ~Gene() { if (information != nullptr) delete[] information; }

	inline void setGene(int gene, int data) { information[gene] = data; }
	inline int getGene(int gene) const { return information[gene]; }

	inline const int* getInformation() const { return information; }
	inline int getLength() const { return length; }

private:
	int* information;
	int length;
};


class Solution {
public:
	Solution(SolutionSettings settings);
	~Solution();

	void createVertexBuffer();
	void createColorBuffer();
	GLuint createVertexArrayObject();
	void createEvalBuffer();

	void mapVertexBuffer();
	void mapColorBuffer();

private:
	// Buffer maps to the vertex buffer and color attrib buffer.
	uint32_t* vertexInformation;
	uint32_t* colorInformation;

	GLuint vertexArrayObject;
	GLuint vertexBuffer;
	GLuint colorBuffer;

	SolutionState state = SolutionState::INVALID;

	Gene* vertexGenes;
	Gene* colorGenes;

	GLuint image;
	GLuint writeTexture;

	GLuint evalBuffer;

	int* vertices;
	int numVertices;
	int* color;
	
};


struct Pixel {
	Pixel() : x(0), y(0) {}
	Pixel(int x, int y) : x(x), y(y) {}
	const int x;
	const int y;
};
