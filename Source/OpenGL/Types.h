#pragma once

/// <summary>
/// Macro representing what OpenGL returns when a function fails to get a valid size.
/// <para> I know you feel like a hacker, but please dont touch this. </para>
/// <para> (This is not an actual OpenGL constant) </para>
/// </summary>
#define GL_INVALID_SIZE 0

namespace OpenGL {
	/// <summary>
	/// Types of data that OpenGL can send to the GPU.
	/// </summary>
	enum class Type {
		NONE			= -1	,
		BYTE			= 0x1400,
		INT				= 0x1404,
		UNSIGNED_INT	= 0x1405,
		FLOAT			= 0x1406
	};

	/// <summary>
	/// Returns the size in bytes of a given OpenGL Type.
	/// </summary>
	size_t getTypeSize(Type type);

	/// <summary>
	/// Types of shaders that OpenGL can compile and link into a shader program.
	/// </summary>
	enum class ShaderType {
		NONE		= -1	,
		VERTEX		= 0x8B31,
		FRAGMENT	= 0x8B30
	};

	/// <summary>
	/// Returns an index corresponding to the given ShaderType.
	/// <para> (From -1 for NONE, +1 for each type in order of declaration) </para>
	/// </summary>
	unsigned int getShaderTypeIndex(ShaderType type);

	/// <summary>
	/// Types of draw calls that OpenGL can perform.
	/// </summary>
	enum class DrawType {
		NONE	= -1	,
		STATIC	= 0x88E4
	};

	/// <summary>
	/// Types of log messages that the logger can output.
	/// </summary>
	enum class LogType {
		INFO,
		WARNING,
		ERROR
	};

	/// <summary>
	/// Returns the color code string for a given LogType.
	/// </summary>
	const char* getLogTypeColor(LogType type);
	/// <summary>
	/// Returns the capitalized string representation of a given LogType.
	/// </summary>
	const char* getLogTypeString(LogType type);
}