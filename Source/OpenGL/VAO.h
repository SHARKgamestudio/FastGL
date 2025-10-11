#pragma once

#include "Object.h"
#include "IBindable.h"

#include "VBO.h"
#include "VBL.h"

namespace OpenGL {
	/// <summary>
	/// Vertex Array object, used to store the links between VBOs and their layouts
	/// </summary>
	class VAO : public Object, public IBindable {
	public:
		VAO();
		~VAO();

		void bind() const override;
		void unbind() const override;

		/// <summary>
		/// Links a VBO to the VAO with a specific layout
		/// </summary>
		/// <param name="vbo">Reference to the VBO to link</param>
		/// <param name="layout">Reference to the layout of the VBO</param>
		void addBuffer(const VBO& vbo, const VBL& layout);
	};
}