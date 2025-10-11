#pragma once

#include "Object.h"
#include "Types.h"

#include <string>

namespace OpenGL {
	/// <summary>
	/// A struct storing every shader source needed for a complete shader program.
	/// </summary>
	struct CombinedShaderSrc {
		std::string vert;
		std::string frag;
		// More shader types will be added later.
	};

	/// <summary>
	/// Parses a single file and extracts every shader source needed for a complete shader program.
	/// <para> The file must contain all stages of the shader program, each stage must be preceded by a custom directive: </para>
	/// <para> (e.g. #shader vert, #shader frag). </para>
	/// </summary>
	/// <param name="path">The file-path to the shader source (can be any extension).</param>
	/// <returns>A CombinedShaderSrc object containing all the sources, separated by shader type.</returns>
	CombinedShaderSrc getCombinedShaderSrcFromFile(const std::string& path);
	/// <summary>
	/// Reads a file and returns its content as a string. (assuming it is a vertex shader source)
	/// <para> If you want, you can add the '#shader vert' directive, to enforce the type of shader. </para>
	/// <para> This will allow the function to return errors if the shader source is not a vertex shader. </para>
	/// </summary>
	/// <param name="path">The file-path to the shader source (can be any extension).</param>
	/// <returns>A string containing the vertex shader source.</returns>
	std::string getVertexShaderSrcFromFile(const std::string& path);
	/// <summary>
	/// Reads a file and returns its content as a string. (assuming it is a fragment shader source)
	/// <para> If you want, you can add the '#shader frag' directive, to enforce the type of shader. </para>
	/// <para> This will allow the function to return errors if the shader source is not a fragment shader. </para>
	/// </summary>
	/// <param name="path">The file-path to the shader source (can be any extension).</param>
	/// <returns>A string containing the fragment shader source.</returns>
	std::string getFragmentShaderSrcFromFile(const std::string& path);

	/// <summary>
	/// Shader object, used to compile and hold OpenGL shaders from source code.
	/// <para> WARNING : Can only be provided with pure GLSL source code. </para>
	/// </summary>
	class Shader : public Object {
	public:
		Shader(const std::string& src, ShaderType type = ShaderType::FRAGMENT);
		~Shader();
	};
}