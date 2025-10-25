#pragma once

#include "../Common/Object.h"
#include "../Common/IBindable.h"

#include "../Utils/Types.h"

namespace OpenGL {
	/// <summary>
	/// Index Buffer object, used to store indices for indexed drawing.
	/// </summary>
	class IBO : public Object, public IBindable {
	public:
		IBO(unsigned int count, const unsigned int* data, DrawType usage = DrawType::STATIC);
		~IBO();

		void bind() const override;
		void unbind() const override;

		/// <summary>
		/// Get the number of indices stored in the IBO.
		/// </summary>
		unsigned int getDataCount() const;

	private:
		unsigned int count;
	};
}