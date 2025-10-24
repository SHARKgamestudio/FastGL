#include "ShaderProgram.h"

#include "Error.h"

#include <iostream>
#include <GL/glew.h>

namespace OpenGL {
	template<typename T>
	inline void ShaderProgram::setUniform(const std::string& name, T value) {
		GL_LOG_ERROR("Unsupported uniform type.");
	}
	template<>
	inline void ShaderProgram::setUniform<float>(const std::string& name, float value) {
		int location = getUniformLocation(name.c_str());
		GL_CALL(glUniform1f(location, value));
	}
	template<>
	inline void ShaderProgram::setUniform<int>(const std::string& name, int value) {
		int location = getUniformLocation(name.c_str());
		GL_CALL(glUniform1i(location, value));
	}
}