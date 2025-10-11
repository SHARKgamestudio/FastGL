#include "Shader.h"

#include "Error.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

namespace OpenGL {
	CombinedShaderSrc getCombinedShaderSrcFromFile(const std::string& path) {
		std::ifstream stream(path);

		std::string line;
		std::stringstream src[2];
		ShaderType type = ShaderType::NONE;
		while (getline(stream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vert") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("frag") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else {
				src[(int)getShaderTypeIndex(type)] << line << "\n";
			}
		}
		return { src[0].str(), src[1].str() };
	}
	std::string getVertexShaderSrcFromFile(const std::string& path) {
		std::ifstream stream(path);

		std::string line;
		std::stringstream src[1];
		while (getline(stream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vert") != std::string::npos) {
					// TO DO : add errors if the shader is not a vertex shader
				}
			}
			else {
				src[0] << line << "\n";
			}
		}
		return src[0].str();
	}
	std::string getFragmentShaderSrcFromFile(const std::string& path) {
		std::ifstream stream(path);

		std::string line;
		std::stringstream src[1];
		while (getline(stream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("frag") != std::string::npos) {
					// TO DO : add errors if the shader is not a fragment shader
				}
			}
			else {
				src[0] << line << "\n";
			}
		}
		return src[0].str();
	}

	Shader::Shader(const std::string& src, ShaderType type) : Object() {
		GL_CALL(id = glCreateShader((unsigned int)type));
		const char* translated = src.c_str();
		GL_CALL(glShaderSource(id, 1, &translated, nullptr));

		// Compile shader
		GLint compiled;
		GL_CALL(glCompileShader(id));
		GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &compiled));
		if (compiled == GL_FALSE) {
			int length;
			GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)_malloca(length * sizeof(char));
			GL_CALL(glGetShaderInfoLog(id, length, &length, message));
			std::cerr << "[OpenGL] ERROR -1 : " << message << "\n";
			GL_CALL(glDeleteShader(id));
		}
	}

	Shader::~Shader() {
		GL_CALL(glDeleteShader(id));
	}
}