#ifndef EXPORT_H
#define EXPORT_H

#ifdef _WIN32
    // For Windows
    #ifdef DLL_EXPORT
        #define DLL_API __declspec(dllexport)
    #else
        #define DLL_API __declspec(dllimport)
    #endif
#else
    // For non-Windows platforms
    #define DLL_API
#endif
#endif
