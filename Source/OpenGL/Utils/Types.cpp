#include "Types.h"

#include <GL/glew.h>

size_t OpenGL::getTypeSize(Type type) {
	switch (type) {
	case OpenGL::Type::BYTE:
		return sizeof(GLbyte);
	case OpenGL::Type::INT:
		return sizeof(GLint);
	case OpenGL::Type::UNSIGNED_INT:
		return sizeof(GLuint);
	case OpenGL::Type::FLOAT:
		return sizeof(GLfloat);
	default:
		return GL_INVALID_SIZE;
	}
}

unsigned int OpenGL::getShaderTypeIndex(ShaderType type) {
	switch (type) {
	case OpenGL::ShaderType::NONE:
		return -1;
	case OpenGL::ShaderType::VERTEX:
		return 0;
	case OpenGL::ShaderType::FRAGMENT:
		return 1;
	default:
		return -1;
	}
}

const char* OpenGL::getLogTypeColor(LogType type) {
	switch (type) {
	case OpenGL::LogType::INFO:
		return "\033[32m";
	case OpenGL::LogType::WARNING:
		return "\033[33m";
	case OpenGL::LogType::ERROR:
		return "\033[31m";
	default:
		return "\033[0m";
	}
}

const char* OpenGL::getLogTypeString(LogType type) {
	switch (type) {
	case OpenGL::LogType::INFO:
		return "INFO";
		break;
	case OpenGL::LogType::WARNING:
		return "WARNING";
		break;
	case OpenGL::LogType::ERROR:
		return "ERROR";
		break;
	default:
		return "UNKNOWN";
		break;
	}
}