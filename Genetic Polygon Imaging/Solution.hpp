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
	void createVertexArrayObject();
	void createEvalBuffer();

	void mapVertexBuffer();
	void mapColorBuffer();

private:
	Gene* genes;

	GLuint image;
	GLuint writeTexture;

	GLuint vertexArrayObject;
	GLuint vertexBuffer;
	GLuint colorBuffer;
	GLuint evalBuffer;

	int* vertices;
	int* color;
	
};
