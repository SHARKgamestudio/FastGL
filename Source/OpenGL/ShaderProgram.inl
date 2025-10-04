#include "ShaderProgram.h"

#include "Error.h"

#include <GL/glew.h>

namespace OpenGL {
	template<typename T>
	inline void ShaderProgram::setUniform(const std::string& name, T value) {
		GL_ASSERT(false);
	}
	template<>
	inline void ShaderProgram::setUniform<float>(const std::string& name, float value) {
		int location = getUniformLocation(name.c_str());
		GL_CALL(glUniform1f(location, value));
	}
}