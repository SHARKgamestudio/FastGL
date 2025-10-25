#pragma once

namespace OpenGL {
	/// <summary>
	/// This is a hotfix and will be removed in future versions.
	/// </summary>
	void SetWorkingDirectory();
}

#define GL_RES_PATH

#ifdef _DEBUG
#define GL_RES_PATH "../../Resources/"
#else
struct dummy { inline dummy() { OpenGL::SetWorkingDirectory(); } };
static dummy s_dummy; // This is a hotfix and will be removed in future versions.

#define GL_RES_PATH "Resources/"
#endif