#pragma once

namespace OpenGL {
	/// <summary>
	/// Base class for OpenGL objects.
	/// <para> We call OpenGL objects, any data linked to an ID assigned by OpenGL. </para>
	/// </summary>
	class Object {
	public:
		unsigned int getID() const;
	protected:
		unsigned int id;
	};
}