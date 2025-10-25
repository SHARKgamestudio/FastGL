#include "ShaderProgram.h"

#include "../Utils/Error.h"

#include <iostream>

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

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
	template<>
	inline void ShaderProgram::setUniform<glm::mat4>(const std::string& name, glm::mat4 value) {
		int location = getUniformLocation(name.c_str());
		GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]));
	}
}