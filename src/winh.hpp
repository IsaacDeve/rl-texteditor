#pragma once

namespace winh {
    #include <iostream>
    #include <string>
    #include <windows.h>
    std::wstring OpenFileDialog() {
        wchar_t filename[MAX_PATH] = {};
    
        OPENFILENAMEW ofn = {};
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFilter = L"All Files\0*.*\0";
        ofn.lpstrFile = filename;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        ofn.lpstrTitle = L"Open File";
    
        if (GetOpenFileNameW(&ofn)) {
            return filename;
        }
    
        return L"";
    }
}
