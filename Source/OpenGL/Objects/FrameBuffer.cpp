#include "FrameBuffer.h"

#include "../Utils/Error.h"

#include "Texture.h"

#include <GL/glew.h>

#define FASTGL_MAX_COLOR_ATTACHMENTS 10

namespace OpenGL {
	FrameBuffer::FrameBuffer() : Object() {
		GL_CALL(glGenFramebuffers(1, &id));
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}

	FrameBuffer::~FrameBuffer() {
		GL_CALL(glDeleteFramebuffers(1, &id));
	}

	void FrameBuffer::attachTexture(const Texture& texture, AttachmentType type) {
		GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)type, GL_TEXTURE_2D, texture.getID(), 0));
	}

	void FrameBuffer::detachTexture(AttachmentType type) {
		GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)type, GL_TEXTURE_2D, 0, 0));
	}

	void FrameBuffer::bind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}

	void FrameBuffer::unbind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}