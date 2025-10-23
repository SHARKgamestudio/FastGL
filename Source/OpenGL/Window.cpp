#include "Window.h"

#include <stdexcept>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Error.h"

#include "VAO.h"
#include "IBO.h"
#include "ShaderProgram.h"

void glfwErrorCallback(int error, const char* description) {
	std::cout << "[ERROR] : " << description << "\n";
}

namespace OpenGL {
	Window::Window(unsigned int width, unsigned int height, const char* title) {
		if (width < MIN_WIDTH || height < MIN_HEIGHT)
			throw std::runtime_error("[ERROR] : Tried to initialize window with a size wich is to small.");

		if (!glfwInit())
			throw std::runtime_error("[ERROR] : There was an error initializing GLFW.");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!m_window)
			throw std::runtime_error("[ERROR] : There was an error creating the GLFW window.");

		glfwMakeContextCurrent(m_window);

		if (glewInit() != GLEW_OK)
			throw std::runtime_error("[ERROR] : There was an error initializing GLEW.");

		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	Window::~Window() {
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	bool Window::shouldClose() const {
		return glfwWindowShouldClose(m_window);
	}

	void Window::pollEvents() {
		glfwPollEvents();
	}

	void Window::clear(const Color& color) {
		GL_CALL(glClearColor(color.r, color.g, color.b, color.a));
	}

	void Window::clear() {
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Window::draw(const VAO& vao, const IBO& ibo, const ShaderProgram& program)
	{
		program.bind();
		vao.bind();
		ibo.bind();

		GL_CALL(glDrawElements(GL_TRIANGLES, ibo.getDataCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Window::swapBuffers() {
		glfwSwapBuffers(m_window);
	}
}