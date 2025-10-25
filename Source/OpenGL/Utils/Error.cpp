#include "Error.h"

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace OpenGL {
	void ClearError() {
		while (glGetError() != GL_NO_ERROR);
	}

	bool CheckError(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError()) {
			Log(std::to_string(error).c_str(), LogType::ERROR, function, file, line);
			return false;
		}
		return true;
	}

	void Log(const char* message, LogType type, const char* function, const char* file, int line) {
		const char* color = getLogTypeColor(type);
		const char* str = getLogTypeString(type);
		std::cout << color << "[OpenGL] " << str << " : " << message << " in " << function << " [" << file << " : line " << line << "] \033[0m" << std::endl;
	}
}