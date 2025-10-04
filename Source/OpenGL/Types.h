#pragma once

#define GL_INVALID_SIZE 0

namespace OpenGL {
	enum class Type {
		NONE			= -1	,
		BYTE			= 0x1400,
		INT				= 0x1404,
		UNSIGNED_INT	= 0x1405,
		FLOAT			= 0x1406
	};

	size_t getTypeSize(Type type);


	enum class ShaderType {
		NONE		= -1	,
		VERTEX		= 0x8B31,
		FRAGMENT	= 0x8B30
	};

	unsigned int getShaderTypeIndex(ShaderType type);

	enum class DrawType {
		NONE	= -1	,
		STATIC	= 0x88E4
	};
}