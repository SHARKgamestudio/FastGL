#pragma once

#include "Object.h"
#include "Types.h"

#include <string>

namespace OpenGL {
	struct CombinedShaderSrc {
		std::string vert;
		std::string frag;
	};

	CombinedShaderSrc getCombinedShaderSrcFromFile(const std::string& path);
	std::string getVertexShaderSrcFromFile(const std::string& path);
	std::string getFragmentShaderSrcFromFile(const std::string& path);

	class Shader : public Object {
	public:
		Shader(const std::string& src, ShaderType type = ShaderType::FRAGMENT);
		~Shader();
	};
}