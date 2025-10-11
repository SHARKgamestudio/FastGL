#pragma once

#include <vector>

#include "Types.h"

namespace OpenGL {
	struct VBLE {
		VBLE() = default;
		VBLE(Type type, unsigned int count, bool normalized);

		Type type;
		unsigned int count;
		bool normalized;
	};

	class VBL {
	public:
		VBL();

		template <typename T>
		void addElement(unsigned int count);

		unsigned int getStride() const;
		const std::vector<VBLE>& getElements() const;

	protected:
	private:
		std::vector<VBLE> elements;
		unsigned int stride;
	};
}

#include "VBL.inl"