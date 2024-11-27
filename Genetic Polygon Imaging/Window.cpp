#include "Window.hpp"

Window::Window(int width, int height, bool vsync) 
    : m_width(width), m_height(height)
{
    if (initialised) return;
    if (!glfwInit()) return;

    // Some initial opengl setup.
    setOpenGLVersion(4, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    
    m_window = glfwCreateWindow(width, height, "", NULL, NULL);
    if (!m_window) return;

    glfwMakeContextCurrent(m_window);
    gladLoadGL();

    if (!vsync) glfwSwapInterval(0);

    initialised = true;
}


Window::~Window() {
    if (m_window != nullptr) close();
}


void Window::setOpenGLVersion(int major, int minor) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}


void Window::close() {
    glfwDestroyWindow(m_window);
    m_window = nullptr;
}


void Window::update() {
    if (glfwWindowShouldClose(m_window)) {
        close();
        return;
    }
    glfwSwapBuffers(m_window);
}



