#include "VBL.h"

namespace OpenGL {
	VBLE::VBLE(Type type, unsigned int count, bool normalized)
		: type(type), count(count), normalized(normalized)
	{}

	VBL::VBL() {
		stride = 0;
	}

	unsigned int VBL::getStride() const {
		return stride;
	}
	const std::vector<VBLE>& VBL::getElements() const {
		return elements;
	}
}