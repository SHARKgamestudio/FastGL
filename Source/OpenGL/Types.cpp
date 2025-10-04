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