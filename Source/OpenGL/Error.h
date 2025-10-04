#pragma once

#include <cassert>

#define GL_ALWAYS_ASSERT_ON_ERROR

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
	void ClearError();
	bool CheckError(const char* function, const char* file, int line);
}