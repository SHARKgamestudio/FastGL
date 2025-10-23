#include "ShaderProgram.h"

#include "Error.h"

#include <iostream>
#include <GL/glew.h>

namespace OpenGL {
	template<typename T>
	inline void ShaderProgram::setUniform(const std::string& name, T value) {
		std::cout << "[OpenGL] ERROR : Unsupported uniform type in ShaderProgram::setUniform<" << typeid(T).name() << ">\n";
		GL_ASSERT(false);
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