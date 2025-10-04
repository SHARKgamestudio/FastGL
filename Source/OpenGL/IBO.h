#pragma once

#include "Object.h"
#include "IBindable.h"

#include "Types.h"

namespace OpenGL {
	class IBO : public Object, public IBindable {
	public:
		IBO(unsigned int count, const unsigned int* data, DrawType usage = DrawType::STATIC);
		~IBO();

		void bind() const override;
		void unbind() const override;

		unsigned int getDataCount() const;

	protected:
		unsigned int count;
	private:
	};
}