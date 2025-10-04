#include "IBO.h"

#include "Error.h"

#include <GL/glew.h>

namespace OpenGL {
	IBO::IBO(unsigned int count, const unsigned int* data, DrawType usage) {
		this->count = count;
		GL_CALL(glGenBuffers(1, &id));
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, (unsigned int)usage));
	}

	IBO::~IBO() {
		GL_CALL(glDeleteBuffers(1, &id));
	}

	void IBO::bind() const {
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
	}

	void IBO::unbind() const {
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	unsigned int IBO::getDataCount() const {
		return count;
	}
}