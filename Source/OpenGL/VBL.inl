#include "VBL.h"

#include "Error.h"

#define GL_INTERNAL_VBL_ADD_TYPE(type, gltype, normalized)	\
template<>													\
inline void VBL::addElement<type>(unsigned int count) {		\
	elements.emplace_back(gltype, count, false);			\
	stride += (unsigned int)getTypeSize(gltype) * count;	\
}															\

namespace OpenGL {
	template<typename T>
	inline void VBL::addElement(unsigned int count) {
		GL_ASSERT(false);
	}

	GL_INTERNAL_VBL_ADD_TYPE(float, Type::FLOAT, false)
	GL_INTERNAL_VBL_ADD_TYPE(unsigned int, Type::UNSIGNED_INT, false)
	GL_INTERNAL_VBL_ADD_TYPE(unsigned char, Type::BYTE, false)
}