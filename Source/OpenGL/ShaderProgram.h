#pragma once

#include "Object.h"
#include "IBindable.h"

#include <unordered_map>
#include <string>

#define GL_AUTO_LINK_PROGRAM
#define GL_AUTO_BIND_PROGRAM

namespace OpenGL {
	class Shader;

	class ShaderProgram : public Object, public IBindable {
	public:
		ShaderProgram();
		~ShaderProgram();

		void attachShader(const Shader& shader);

		void bind() const override;
		void unbind() const override;

		template <typename T>
		void setUniform(const std::string& name, T value);
	protected:
	private:
		std::unordered_map<const char*, int> locations;
		int getUniformLocation(const char* name);

		mutable bool linked;
		void link() const;
	};
}

#include "ShaderProgram.inl"