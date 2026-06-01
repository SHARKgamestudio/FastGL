#pragma once

#include <chrono>

#include "../Utils/Event.h"

#include <GLM/vec2.hpp>

/// <summary>
/// Dont mind this, it's just to avoid idiots from having fun with the window size.
/// <para> And you are not an idiot, are you ? </para>
/// <para> ..Are you ? </para>
/// </summary>
#define MIN_WIDTH	64
/// <summary>
/// Dont mind this, it's just to avoid idiots from having fun with the window size.
/// <para> And you are not an idiot, are you ? </para>
/// <para> ..Are you ? </para>
/// </summary>
#define MIN_HEIGHT	64

struct GLFWwindow;
struct GLFWimage;

namespace OpenGL {
	class VAO;
	class IBO;
	class ShaderProgram;

	struct TextureSrc;

	/// <summary>
	///	Temporary color structure.
	/// <para> Will be replaced by a more complete Color class in the future. </para>
	/// </summary>
	struct Color {
		float r, g, b, a;
	};

	/// <summary>
	/// Abstraction of a GLFW window.
	/// <para> Even if also providing basic methods for rendering, this has nothign to do with OpenGL itself. </para>
	/// <para> Meaning you can use the rest of the library without using this class at all. </para>
	/// <para> (with your own windowing system, for exemple) </para>
	/// </summary>
	class Window {
	public:
		/// <summary>
		/// Simple enum defining the window display mode.
		/// <para> Can be overridden by OS-specific window decoration commands. </para>
		/// </summary>
		enum WinMode : char {
			MODE_WINDOWED	= 0,
			MODE_FULLSCREEN	= 1,
			MODE_BORDERLESS	= 2,
		};

		Window(unsigned int width, unsigned int height, const char* title);
		~Window();

		/// <summary>
		/// Event that fires each frames while the window is being resized.
		/// <para> Usually used to keep rendering during window resizing, since the event loop stalls during this operation. </para>
		/// </summary>
		Event<int, int> OnResize;

		/// <summary>
		/// Checks if the window should close.
		/// <para> Generaly used to know when to exit the main application loop. </para>
		/// </summary>
		/// <returns> Returns true if the close button of the window has been pressed. </returns>
		bool shouldClose() const;
		
		/// <summary>
		/// Polls for window events using GLFW.
		/// </summary>
		void pollEvents();

		/// <summary>
		/// Get the current size of the window.
		/// </summary>
		/// <returns> Returns the width & height of the window (in px).</returns>
		glm::vec2 getSize();

		/// <summary>
		/// Swaps the contents of the front and back buffers.
		/// </summary>
		void swapBuffers();

		/// <summary>
		/// Clears the window with a specific color.
		/// </summary>
		void clear(const Color& color);
		/// <summary>
		/// Clears the window with black.
		/// </summary>
		void clear();

		/// <summary>
		/// Set the window icon in both the taskbar and title bar.
		/// </summary>
		/// <param name="iconSrc">Reference to the TextureSource to use.</param>
		void setIcon(const TextureSrc& iconSrc);

		/// <summary>
		/// Set the window display mode.
		/// </summary>
		/// <param name="mode">Display mode to use, options are : windowed, fullscreen, borderless-fullscreen.</param>
		void setWindowMode(WinMode mode);

		/// <summary>
		/// Get the current window display mode.
		/// </summary>
		/// <returns> Returns the display mode, options are : windowed, fullscreen, borderless-fullscreen.</returns>
		WinMode getWindowMode() const;

		/// <summary>
		/// Draws the given IBO indices of the VAO using the given ShaderProgram.
		/// <para> This is just an abstraction of 'glDrawElements', you dont need to use this.</para>
		/// <para> You can write your own renderer if you want, this is just provided for getting started quickly.</para>
		/// </summary>
		/// <param name="vao">Reference to the VAO to draw.</param>
		/// <param name="ibo">Reference to the IBO defining the indices of the VAO to draw.</param>
		/// <param name="program">Reference to the ShaderProgram to use for drawing.</param>
		void draw(const VAO& vao, const IBO& ibo, const ShaderProgram& program);

		/// <summary>
		/// Draws the given IBO indices of the VAO using the given ShaderProgram multiple times.
		/// <para> This is just an abstraction of 'glDrawElementsInstanced', you dont need to use this.</para>
		/// <para> You can write your own renderer if you want, this is just provided for getting started quickly.</para>
		/// </summary>
		/// <param name="vao">Reference to the VAO to draw.</param>
		/// <param name="ibo">Reference to the IBO defining the indices of the VAO to draw.</param>
		/// <param name="program">Reference to the ShaderProgram to use for drawing.</param>
		/// <param name="count">The number of times you want to draw your element.</param>
		void drawInstanced(const VAO& vao, const IBO& ibo, const ShaderProgram& program, int count);

		/// <summary>
		/// Get the time the current frame took to process.
		/// </summary>
		/// <returns> Returns the time delta as a float, in seconds. </returns>
		float getDeltaTime() const;

		/// <summary>
		/// Gets the internal GLFW window handle.
		/// </summary>
		/// <returns>  Returns a pointer to the internal GLFW window opaque structure used by this instance of the window abstraction class. </returns>
		GLFWwindow* getHandle() const;

	private:
		GLFWwindow* m_window;
		GLFWimage* m_icon;

		WinMode m_mode;

		int posX, posY;
		int sizeX, sizeY;

		std::chrono::steady_clock::time_point current;
		std::chrono::steady_clock::time_point previous;
		float delta;
	};
}