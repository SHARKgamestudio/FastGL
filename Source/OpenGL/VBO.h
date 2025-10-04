#pragma once

#include "Object.h"
#include "IBindable.h"

#include "Types.h"

namespace OpenGL {
	class VBO : public Object, public IBindable {
	public:
		VBO(__int64 size, const void* data, DrawType usage = DrawType::STATIC);
		~VBO();

		void bind() const override;
		void unbind() const override;

	protected:
	private:
	};
}