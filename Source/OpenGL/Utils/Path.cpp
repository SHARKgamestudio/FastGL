#include "Path.h"

#include <windows.h>
#include <string>

namespace OpenGL {
    void SetWorkingDirectory() {
        wchar_t exePath[MAX_PATH];
        GetModuleFileNameW(nullptr, exePath, MAX_PATH);

        std::wstring path(exePath);

        size_t pos = path.find_last_of(L"\\/");
        if (pos != std::wstring::npos)
        {
            path = path.substr(0, pos);
            SetCurrentDirectoryW(path.c_str());
        }
    }
}