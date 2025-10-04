#include "VAO.h"

#include "Error.h"

#include <GL/glew.h>

namespace OpenGL {
	VAO::VAO() {
		GL_CALL(glGenVertexArrays(1, &id));
		GL_CALL(glBindVertexArray(id));
	}

	VAO::~VAO() {
		GL_CALL(glDeleteVertexArrays(1, &id));
	}

	void VAO::bind() const {
		GL_CALL(glBindVertexArray(id));
	}

	void VAO::unbind() const {
		GL_CALL(glBindVertexArray(0));
	}

	void VAO::add(const VBO& vbo, const VBL& layout) {
		vbo.bind();

		const std::vector<VBLE>& elements = layout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const VBLE& element = elements[i];
			GL_CALL(glEnableVertexAttribArray(i));
			GL_CALL(glVertexAttribPointer(i, element.count, (unsigned int)element.type, element.normalized, layout.getStride(), (const void*)offset));
			offset += element.count * (unsigned int)getTypeSize(element.type);
		}
	}
}