// dll entry

#include "Windows.h"
#include "stdio.h"
#include "iostream"


// thread is always
DWORD __stdcall Main(LPVOID lpvReserved) {
    AllocConsole();
    // freopen_s

    FILE* fileptr;

    // file double ptr cuz we used * to indicate fileptr is a FILE (type) pointer
    // & returns a pointer to the original var
    // our case is a file ptr so double ptr because ur referencing a ptr

    freopen_s(&fileptr, "CONOUT$", "w", stdout);

    std::cout << "PUNJABI SDK INJECTED"<<std::endl;

    while (!GetAsyncKeyState(VK_END)) {
        Sleep(100);
    }

    // uninject
    std::cout << "PUNJABI SDK UNINJECTING" << std::endl;
    Sleep(1000);
    fclose(fileptr);
    FreeConsole();
    FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(lpvReserved), 0);

    return 1;
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved)  // reserved
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.

        CreateThread(nullptr, 0, Main, hinstDLL, 0, nullptr);
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:

        if (lpvReserved != nullptr)
        {
            break; // do not do cleanup if process termination scenario
        }

        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}