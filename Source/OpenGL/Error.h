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

#ifdef _DEBUG
#ifdef _MSC_VER
#define GL_ASSERT(func) if(!(func)) __debugbreak();
#else
#define GL_ASSERT(func) assert(func);
#endif
#ifdef GL_ALWAYS_ASSERT_ON_ERROR
#define GL_CALL(func) OpenGL::ClearError(); \
					  func;\
					  GL_ASSERT(OpenGL::CheckError(#func, __FILE__, __LINE__))
#else
#define GL_CALL(func) OpenGL::ClearError(); \
					  func;\
					  OpenGL::CheckError(#func, __FILE__, __LINE__)
#endif
#else
#define GL_ASSERT(func) func
#define GL_CALL(func) func
#endif

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
	bool CheckError(const char* function, const char* file, int line);
}