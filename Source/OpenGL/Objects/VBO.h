#pragma once

#include "../Common/Object.h"
#include "../Common/IBindable.h"

#include "../Utils/Types.h"

namespace OpenGL {
	/// <summary>
	/// Vertex Buffer object, used to store vertex data in the GPU memory.
	/// </summary>
	class VBO : public Object, public IBindable {
	public:
		VBO(__int64 size, const void* data, DrawType usage = DrawType::STATIC);
		~VBO();

		void bind() const override;
		void unbind() const override;
	};
}