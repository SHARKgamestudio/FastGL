#pragma once

namespace OpenGL {
	class Object {
	public:
		unsigned int getID() const;
	protected:
		unsigned int id;
	};
}