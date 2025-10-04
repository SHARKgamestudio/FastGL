#pragma once

namespace OpenGL {
	class IBindable {
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}