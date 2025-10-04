#include "VBO.h"

#include "Error.h"

#include <GL/glew.h>

namespace OpenGL {
	VBO::VBO(__int64 size, const void* data, DrawType usage) {
		GL_CALL(glGenBuffers(1, &id));
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, id));
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, (unsigned int)usage));
	}

	VBO::~VBO() {
		GL_CALL(glDeleteBuffers(1, &id));
	}

	void VBO::bind() const {
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, id));
	}

	void VBO::unbind() const {
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}