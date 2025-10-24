#pragma once

#include <cassert>

/// <summary>
/// Undefine this macro to disable assertions on OpenGL errors in debug mode.
/// </summary>
#define GL_ALWAYS_ASSERT_ON_ERROR

/// <summary>
/// Multi-compiler assertion macro.
/// <para> In debug mode, it will trigger a breakpoint (on MSVC) or call assert (on other compilers). </para>
/// </summary>
#define Gl_ASSERT(func)

/// <summary>
/// OpenGL function call wrapper with error checking.
/// <para> In debug mode, it clears previous errors, calls the function, and checks for new errors. </para>
/// </summary>
#define GL_CALL(func)

#define GL_LOG_INFO(message)
#define GL_LOG_WARNING(message)
#define GL_LOG_ERROR(message)

#ifdef _DEBUG

#define GL_LOG_INFO(message) OpenGL::Log(message, OpenGL::LogType::INFO, __FUNCTION__, __FILE__, __LINE__)
#define GL_LOG_WARNING(message) OpenGL::Log(message, OpenGL::LogType::WARNING, __FUNCTION__, __FILE__, __LINE__)

#ifdef _MSC_VER
#define GL_ASSERT(func) if(!(func)) __debugbreak();
#else
#define GL_ASSERT(func) assert(func);
#endif
#ifdef GL_ALWAYS_ASSERT_ON_ERROR
#define GL_CALL(func) OpenGL::ClearError(); \
					  func;\
					  GL_ASSERT(OpenGL::CheckError(#func, __FILE__, __LINE__))
#define GL_LOG_ERROR(message) OpenGL::Log(message, OpenGL::LogType::ERROR, __FUNCTION__, __FILE__, __LINE__); \
							  GL_ASSERT(false)
#else
#define GL_CALL(func) OpenGL::ClearError(); \
					  func;\
					  OpenGL::CheckError(#func, __FILE__, __LINE__)
#define GL_LOG_ERROR(message) OpenGL::Log(message, OpenGL::LogType::ERROR, __FUNCTION__, __FILE__, __LINE__)
#endif
#else
#define GL_ASSERT(func) func
#define GL_CALL(func) func
#endif

#include "Types.h"

namespace OpenGL {
	/// <summary>
	/// Clears all existing OpenGL errors.
	/// </summary>
	void ClearError();

	/// <summary>
	/// Checks for OpenGL errors and logs them.
	/// <para> WARNING: It is recommended to use the GL_CALL macro instead of calling this function directly. </para>
	/// </summary>
	/// <param name="function">Name of the function for which the check is performed.</param>
	/// <param name="file">File name where the function is called.</param>
	/// <param name="line">Line number where the function is called.</param>
	/// <returns>True if no errors were found, false otherwise.</returns>
	bool CheckError(const char* function, const char* file, int line);

	/// <summary>
	/// Logs a message with custom format and colors based on the log type.
	/// <para> WARNING: It is recommended to use the GL_LOG_* macros instead of calling this function directly. </para>
	/// </summary>
	/// <param name="message">The message to log.</param>
	/// <param name="type">The type of log message (INFO, WARNING, ERROR).</param>
	/// <param name="function">Name of the function for which the check is performed.</param>
	/// <param name="file">File name where the function is called.</param>
	/// <param name="line">Line number where the function is called.</param>
	void Log(const char* message, LogType type, const char* function, const char* file, int line);
}