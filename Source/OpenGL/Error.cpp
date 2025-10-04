#include "Error.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OpenGL {
	void ClearError() {
		while (glGetError() != GL_NO_ERROR);
	}

	bool CheckError(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError()) {
			std::cout << "[OpenGL] ERROR " << error << " : " << function << " in [" << file << " : line " << line << "]\n";
			return false;
		}
		return true;
	}
}