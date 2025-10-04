#include "ShaderProgram.h"

#include "Error.h"

#include "Shader.h"

#include <GL/glew.h>

#include <iostream>

namespace OpenGL {
	ShaderProgram::ShaderProgram() {
		GL_CALL(id = glCreateProgram());
		GL_CALL(glBindFragDataLocation(id, 0, "outColor"));
	}

	ShaderProgram::~ShaderProgram() {
		GL_CALL(glDeleteProgram(id));
	}

	void ShaderProgram::attachShader(const Shader& shader) {
		GL_CALL(glAttachShader(id, shader.getID()));
	}

	void ShaderProgram::bind() const {
		GL_CALL(glLinkProgram(id));
		GL_CALL(glUseProgram(id));
	}

	void ShaderProgram::unbind() const {
		GL_CALL(glLinkProgram(0));
		GL_CALL(glUseProgram(0));
	}

	int ShaderProgram::getUniformLocation(const char* name) {
		if (locations.find(name) != locations.end()) {
			return locations[name];
		}

		GL_CALL(int location = glGetUniformLocation(id, name));
		if (location == -1)
			std::cout << "[OpenGL] WARNING : uniform '" << name << "' doesn't exist, on shader '" << id << "' !\n";
		locations[name] = location;
		return location;
	}
}