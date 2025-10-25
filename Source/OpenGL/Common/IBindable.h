#pragma once

namespace OpenGL {
	/// <summary>
	/// Interface for OpenGL objects wich possess 'bind' and 'unbind' methods.
	/// </summary>
	class IBindable {
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}