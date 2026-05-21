#include "Window.h"

#include <stdexcept>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Utils/Error.h"

#include "../Objects/VAO.h"
#include "../Objects/IBO.h"
#include "../Objects/Texture.h"
#include "../Objects/ShaderProgram.h"

void glfwErrorCallback(int error, const char* description) {
	std::cout << "[ERROR] : " << description << "\n";
}

void glfwResizeCallback(GLFWwindow* g_window, int width, int height) {
	glViewport(0, 0, width, height);

	OpenGL::Window* glWindow = static_cast<OpenGL::Window*>(glfwGetWindowUserPointer(g_window));
	glWindow->OnResize.invoke(width, height);
}

namespace OpenGL {
	Window::Window(unsigned int width, unsigned int height, const char* title) {
		if (width < MIN_WIDTH || height < MIN_HEIGHT) {
			GL_LOG_ERROR("Tried to initialize window with a size wich is to small.")
		}

		if (!glfwInit()) {
			GL_LOG_ERROR("There was an error initializing GLFW.")
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!m_window) {
			GL_LOG_ERROR("There was an error creating the GLFW window.");
		}

		m_icon = new GLFWimage();
		m_icon->pixels = nullptr;
		m_icon->width = 0;
		m_icon->height = 0;

		glfwMakeContextCurrent(m_window);

		glfwSetWindowUserPointer(m_window, this);

		if (glfwSetFramebufferSizeCallback(m_window, glfwResizeCallback)) {
			GL_LOG_ERROR("There was an error setting the GLFW resize callback.");
		}

		if (glewInit() != GLEW_OK) {
			GL_LOG_ERROR("There was an error initializing GLEW.");
		}

		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


		// save current window transforms
		glfwGetWindowPos(m_window, &posX, &posY);
		glfwGetWindowSize(m_window, &sizeX, &sizeY);
		m_mode = MODE_WINDOWED;
	}

	Window::~Window() {
		glfwDestroyWindow(m_window);
		delete m_icon;
		glfwTerminate();
	}

	bool Window::shouldClose() const {
		return glfwWindowShouldClose(m_window);
	}

	void Window::pollEvents() {
		glfwPollEvents();
	}

	glm::vec2 Window::getSize() {
		int width = -1;
		int height = -1;
		glfwGetWindowSize(m_window, &width, &height);

		return glm::vec2((float)width, (float)height);
	}

	void Window::clear(const Color& color) {
		GL_CALL(glClearColor(color.r, color.g, color.b, color.a));
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Window::clear() {
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Window::setIcon(const TextureSrc& iconSrc) {
		m_icon->width = iconSrc.width;
		m_icon->height = iconSrc.height;
		m_icon->pixels = iconSrc.data;

		glfwSetWindowIcon(m_window, 1, m_icon);
	}

	void Window::setWindowMode(WinMode mode) {
		m_mode = mode;

		switch (mode) {
		case MODE_WINDOWED: {
			// restore window decorations
			glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_TRUE);

			// reset window state to previous state
			glfwSetWindowMonitor(m_window, nullptr, posX, posY, sizeX, sizeY, 0);
		}
		break;
		case MODE_FULLSCREEN: {
			// get monitor properties (such as resolution)
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();

			if (monitor == nullptr) {
				GL_LOG_ERROR("There was an error getting the GLFW monitor.");
			}

			// save current window transforms
			glfwGetWindowPos(m_window, &posX, &posY);
			glfwGetWindowSize(m_window, &sizeX, &sizeY);

			// get resolution of monitor
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			if (mode == nullptr) {
				GL_LOG_ERROR("There was an error getting the GLFW video mode.");
			}

			// switch to full screen
			glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
		}
		break;
		case MODE_BORDERLESS: {
			// get monitor properties (such as resolution)
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();

			if (monitor == nullptr) {
				GL_LOG_ERROR("There was an error getting the GLFW monitor.");
			}

			// save current window transforms
			glfwGetWindowPos(m_window, &posX, &posY);
			glfwGetWindowSize(m_window, &sizeX, &sizeY);

			// get resolution of monitor
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			if (mode == nullptr) {
				GL_LOG_ERROR("There was an error getting the GLFW video mode.");
			}

			// remove window decorations
			glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_FALSE);

			// switch to borderless fullscreen
			glfwSetWindowMonitor(m_window, nullptr, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
		}
		break;
		default:
		break;
		}
	}

	void Window::draw(const VAO& vao, const IBO& ibo, const ShaderProgram& program) {
		program.bind();
		vao.bind();
		ibo.bind();

		GL_CALL(glDrawElements(GL_TRIANGLES, ibo.getDataCount(), GL_UNSIGNED_INT, nullptr));
	}

	GLFWwindow* Window::getHandle() const {
		return m_window;
	}

	Window::WinMode Window::getWindowMode() const {
		return m_mode;
	}

	void Window::swapBuffers() {
		glfwSwapBuffers(m_window);
	}
}