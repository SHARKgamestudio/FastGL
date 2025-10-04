#pragma once

#define MIN_WIDTH	64
#define MIN_HEIGHT	64

struct GLFWwindow;

namespace OpenGL {
	class Window {
	public:
		Window(unsigned int width, unsigned int height, const char* title);
		~Window();

		bool shouldClose() const;

		void pollEvents();
		void swapBuffers();

		void clear();
		//void draw();
	protected:
	private:
		GLFWwindow* m_window;
	};
}