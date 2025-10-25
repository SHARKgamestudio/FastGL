#pragma once

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

namespace OpenGL {
	class VAO;
	class IBO;
	class ShaderProgram;

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
		Window(unsigned int width, unsigned int height, const char* title);
		~Window();

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
		/// Draws the given IBO indices of the VAO using the given ShaderProgram.
		/// <para> This is just an abstraction of 'glDrawElements', you dont need to use this.</para>
		/// <para> You can write your own renderer if you want, this is just provided for getting started quickly.</para>
		/// </summary>
		/// <param name="vao">Reference to the VAO to draw.</param>
		/// <param name="ibo">Reference to the IBO defining the indices of the VAO to draw.</param>
		/// <param name="program">Reference to the ShaderProgram to use for drawing.</param>
		void draw(const VAO& vao, const IBO& ibo, const ShaderProgram& program);

	private:
		GLFWwindow* m_window;
	};
}