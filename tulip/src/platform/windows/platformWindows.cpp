#include "tulippch.h"
#include "platformWindows.h"

#include <application\application.h>

#include <commdlg.h>

const std::string tulip::PlatformWindows::openFileImpl(const char* filter) {

    OPENFILENAMEA ofn = {};
    CHAR szFile[512] = { 0 };
    ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
    ofn.lStructSize = sizeof(OPENFILENAMEA);
    ofn.hwndOwner = (HWND) *Application::getMainWindow()->getWindowHandle();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileNameA(&ofn) == TRUE) {
        return ofn.lpstrFile;
    }

    return "";
}

const std::string tulip::PlatformWindows::saveFileImpl(const char* filter) {

    OPENFILENAMEA ofn = {};
    CHAR szFile[260] = { 0 };
    ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
    ofn.lStructSize = sizeof(OPENFILENAMEA);
    ofn.hwndOwner = (HWND)*Application::getMainWindow()->getWindowHandle();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetSaveFileNameA(&ofn) == TRUE) {
        return ofn.lpstrFile;
    }

    return "";
}
