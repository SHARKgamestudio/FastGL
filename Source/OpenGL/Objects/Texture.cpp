#include "Texture.h"

#include "../Utils/Error.h"

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STBI/stbimage.h>

namespace OpenGL {
	TextureSrc getTextureSrcFromFile(const std::string& path) {
		stbi_set_flip_vertically_on_load(1);

		TextureSrc src;
		src.data = stbi_load(path.c_str(), &src.width, &src.height, &src.channels, 4);

		return src;
	}
	TextureSrc::~TextureSrc() {
		stbi_image_free(data);
		data = nullptr;
	}

	Texture::Texture(const TextureSrc& src) {
		GL_CALL(glGenTextures(1, &id));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, id));

		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, src.width, src.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, src.data));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
	}

	Texture::~Texture() {
		GL_CALL(glDeleteTextures(1, &id));
	}

	void Texture::bind() const {
		GL_CALL(glActiveTexture(GL_TEXTURE0));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, id));
	}

	void Texture::unbind() const {
		GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
	}
}