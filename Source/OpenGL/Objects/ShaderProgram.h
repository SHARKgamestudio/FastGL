#pragma once

#include "../Common/Object.h"
#include "../Common/IBindable.h"

#include <unordered_map>
#include <string>

/// <summary>
/// If defined, shader programs will try to automatically link themselves before executing operations that require it, to ensure safety.
/// <para> WARNING : This behavior is active by default, but can be disabled by undefining this macro. </para>
/// </summary>
#define GL_AUTO_LINK_PROGRAM
/// <summary>
/// If defined, shader programs will try to automatically bind themselves before executing operations that require it, to ensure safety.
/// <para> WARNING : This behavior is active by default, but can be disabled by undefining this macro. </para>
/// </summary>
#define GL_AUTO_BIND_PROGRAM

namespace OpenGL {
	class Shader;

	/// <summary>
	/// Shader Program object, defines a complete GPU programable pipeline made of multiple shaders.
	/// <para> This is also where you would set uniforms. </para>
	/// </summary>
	class ShaderProgram : public Object, public IBindable {
	public:
		ShaderProgram();
		~ShaderProgram();

		/// <summary>
		/// Attaches a Shader object to the shader program.
		/// </summary>
		/// <param name="shader">Reference to the Shader object to attach.</param>
		void attachShader(const Shader& shader);

		void bind() const override;
		void unbind() const override;

		/// <summary>
		/// Sets a uniform's value by name.
		/// <para> Supported types are : float, </para>
		/// <para> More types will be supported in the future. </para>
		/// </summary>
		/// <typeparam name="T">Type of the uniform to set.</typeparam>
		/// <param name="name">Name of the uniform to set.</param>
		/// <param name="value">Value to set the uniform to.</param>
		template <typename T>
		void setUniform(const std::string& name, T value);
	private:
		std::unordered_map<const char*, int> locations;
		int getUniformLocation(const char* name);

		mutable bool linked;
		void link() const;
	};
}

#include "ShaderProgram.inl"