#pragma once

#include "glad/glad.h"
/********************************************************************
 * @file   Renderer.hpp
 * @brief  Code related to drawing to the screen.
 * 
 * File contains code related to drawing to the screen. This includes
 * the binding of shaders and vertex array object, drawing by vertex
 * or by element, and using any draw type (e.g GL_TRIANGLES).
 * 
 * @author Thomas Johnson
 * @date   November 2024
 *********************************************************************/

#include "Shader.hpp"

/**
 * @class Renderer.
 * @brief Handles drawing to the screen.
 */
class Renderer {
public:
	Renderer();
	Renderer(const Renderer& other) = delete;

	~Renderer();

	inline void setShader(Shader program) { m_shader = program; }
	inline Shader getShader() const { return m_shader; }

	static inline Renderer* getInstance() { return instance; }
	static inline bool isInitialised() { return initialised; }

private:
	Shader m_shader;
	
	static inline bool initialised = false;
	static inline Renderer* instance = nullptr;
};
