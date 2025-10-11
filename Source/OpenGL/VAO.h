#pragma once

#include "Object.h"
#include "IBindable.h"

#include "VBO.h"
#include "VBL.h"

namespace OpenGL {
	class VAO : public Object, public IBindable {
	public:
		VAO();
		~VAO();

		void bind() const override;
		void unbind() const override;

		void addBuffer(const VBO& vbo, const VBL& layout);
	protected:
	private:
	};
}