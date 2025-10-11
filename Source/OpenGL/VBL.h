#pragma once

#include "Types.h"

#include <vector>

namespace OpenGL {
	/// <summary>
	/// Data structure representing a single element of the layout of a vertex buffer.
	/// <para> WARNING : This is not an OpenGL concept, it is just a helper structure to make layout more manageable. </para>
	/// </summary>
	struct VBLE {
		VBLE() = default;
		VBLE(Type type, unsigned int count, bool normalized);

		Type type;
		unsigned int count;
		bool normalized;
	};

	/// <summary>
	/// Wrapper class representing the layout of a vertex buffer.
	/// <para> WARNING : This is not a real OpenGL object, it does not have any ID. </para>
	/// </summary>
	class VBL {
	public:
		VBL();
		/// <summary>
		/// Add an element definition to the layout.
		/// <para>
		/// Supported types are : float, unsigned int, unsigned char,
		/// </para>
		/// <para>
		/// More types will be supported in the future.
		/// </para>
		/// </summary>
		/// <typeparam name="T">The type of the element to add.</typeparam>
		/// <param name="count">The number of components of the element to add.</param>
		template <typename T>
		void addElement(unsigned int count);

		/// <summary>
		/// Get the total stride of the layout, in bytes.
		/// </summary>
		/// <returns>The total stride of the layout, in bytes.</returns>
		unsigned int getStride() const;
		/// <summary>
		/// Get all the elements of the layout.
		/// </summary>
		/// <returns>A vector containing all the elements of the layout.</returns>
		const std::vector<VBLE>& getElements() const;

	private:
		std::vector<VBLE> elements;
		unsigned int stride;
	};
}

#include "VBL.inl"