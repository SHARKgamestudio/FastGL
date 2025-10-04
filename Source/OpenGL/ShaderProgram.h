#pragma once

#include "Object.h"
#include "IBindable.h"

#include <unordered_map>
#include <string>

namespace OpenGL {
	class Shader;

	struct float4 {
		float x, y, z, w;
	};

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
	};
}

#include "ShaderProgram.inl"