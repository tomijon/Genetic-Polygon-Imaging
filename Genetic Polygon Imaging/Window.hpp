#pragma once

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"


class Window {
public:
	Window(int width, int height, bool vsync = true);
	Window(const Window& other) = delete;
	Window(Window&& other) : m_width(other.m_width), m_height(other.m_height), m_window(other.m_window) {
		other.m_width = 0;
		other.m_height = 0;
		other.m_window = nullptr;
	}

	~Window();

	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }

	inline void hideMouse() { glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); }
	inline void showMouse() { glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

	inline void setTitle(const std::string& name) { glfwSetWindowTitle(m_window, name.c_str()); }

	void setOpenGLVersion(int major, int minor);

	void close();
	void update();
	inline bool isOpen() const { return m_window != nullptr; }

	static inline Window* getInstance() { return instance; }
	static inline bool isInitialised() { return initialised; }


private:
	int	m_width = 0;
	int	m_height = 0;

	GLFWwindow* m_window = nullptr;

	static inline bool initialised = false;
	static inline Window* instance = nullptr;
};

