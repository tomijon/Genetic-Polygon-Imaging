#pragma once

#include <mutex>
#include <thread>

#include "glad/glad.h"


struct SolutionSettings {
	//SolutionSettings(const std::string& config);

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

	const int WIDTH;
	const int HEIGHT;
};


enum SolutionState {
	INVALID = 0,
	VALID = 1,
	EVALUATED = 2,
};


class Gene {
public:
	Gene() : information(nullptr), length(0) {}
	Gene(const int size) : information(new GLuint[size]), length(size) {}
	Gene(const int size, GLuint* data) : information(data), length(size) {}
	
	Gene(const Gene& other) : information(new GLuint[other.length]), length(other.length) {
		for (int i = 0; i < length; i++) {
			information[i] = other.information[i];
		}
	}

	Gene(Gene&& other) noexcept : information(other.information), length(other.length) {
		other.information = nullptr;
	}
	
	virtual ~Gene() { if (information != nullptr) delete[] information; }

	inline void setGene(int gene, GLuint data) { information[gene] = data; }
	inline int getGene(int gene) const { return information[gene]; }

	inline const GLuint* getInformation() const { return information; }
	inline int getLength() const { return length; }

	Gene operator=(const Gene& other) {
		length = other.length;
		information = new GLuint[length];

		for (int i = 0; i < length; i++) {
			information[i] = other.information[i];
		}
		return *this;
	}

	Gene operator=(Gene&& other) noexcept {
		information = other.information;
		length = other.length;
		other.information = nullptr;
		return *this;
	}


private:
	GLuint* information;
	int length;
};


class Solution {
public:
	Solution(SolutionSettings settings);
	~Solution();

	void initVertexBuffer();
	void initColorBuffer();
	void initEvalBuffer();
	void initFramebuffer();
	void initDrawTexture();
	void mapGenes();

	void flushBuffers();
	void draw();

	inline GLuint getResultImage() const { return drawTexture; }
	inline SolutionState getState() const { return state; }
	inline unsigned int getWidth() const { return width; }
	inline unsigned int getHeight() const { return height; }

private:
	// Buffer maps to the vertex buffer and color attrib buffer.
	GLuint* vertexInformation = nullptr;
	GLuint* colorInformation = nullptr;
	GLuint* elementInformation = nullptr;
	GLfloat* evalResults = nullptr;

	// OpenGL Buffers.
	GLuint vertexArrayObject = 0;
	GLuint vertexBuffer = 0;
	GLuint colorBuffer = 0;
	GLuint elementBuffer = 0;	// numVertices + maxPolygons

	GLuint evalBuffer = 0;	// Buffer storing MSE results.
	GLuint framebuffer = 0;	// Where texture will be drawn.
	GLuint drawTexture = 0; // Texture to draw to.

	SolutionState state = SolutionState::INVALID;

	// Maps to vertexInformation and colorInformation.
	// Used for genetic operations.
	Gene* vertexGenes = nullptr;
	Gene* colorGenes = nullptr;

	// General data.
	const unsigned int verticesPerPolygon;
	const unsigned int maxPolygons;
	int currentPolygons = 0;

	const int numVertices;
	const int width;
	const int height;
};


struct Pixel {
	Pixel() : x(0), y(0) {}
	Pixel(int x, int y) : x(x), y(y) {}
	const int x;
	const int y;
};
