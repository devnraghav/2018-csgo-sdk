// dll entry

#include "Windows.h"
#include "stdio.h"
#include "iostream"
#include "base_offsets.h"
#include <string>

#include <vector>


// whats an interface manager?
// a class that doesn't contain member variables and only has pure virtual functions.
// interface is a way for developers to let other developers know what to implement when using an sdk.
// VMT hooking
// 
// creating Getinterface function thanks to Cazz.

template <typename T>
T* GetInterface(const char* name, const char* lib) {

    // name depends

    const auto handle = GetModuleHandle(lib);

    // if we can't get a handle to the library we return null
    if (!handle)
        return nullptr;

    const auto functionAddress = GetProcAddress(handle, "CreateInterface");

    if (!functionAddress)
        return nullptr;

    // FUCK THIS SYNTAX BRO
    using function = T * (*)(const char*, int*);
    const auto CreateInterface = reinterpret_cast<function>(functionAddress);

    // congrats! now you can call this function
    return CreateInterface(name, nullptr);
}

// entity class with a method that gets the entity's health assuming it's valid (i.e CBaseplayer)
class CEntity
{
public:
    const int& GetHealth() const noexcept
    {
        return *reinterpret_cast<int*>(std::uintptr_t(this) + m_iHealth);
    }

    const int& IsLocalPlayer() const noexcept
    {
        return *reinterpret_cast<int*>(std::uintptr_t(this) + dwLocalPlayer);
    }
};

// interface definition from source sdk 2013. We can use many others too.
class IClientEntityList
{
public:
    // Get IClientNetworkable interface for specified entity
    virtual void* GetClientNetworkable(int entnum) = 0;
    virtual void* GetClientNetworkableFromHandle(DWORD hEnt) = 0;
    virtual void* GetClientUnknownFromHandle(DWORD hEnt) = 0;

    // NOTE: This function is only a convenience wrapper.
    // It returns GetClientNetworkable( entnum )->GetIClientEntity().
    virtual CEntity* GetClientEntity(int entnum) = 0;
    virtual CEntity* GetClientEntityFromHandle(DWORD hEnt) = 0;

    // Returns number of entities currently in use
    virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;

    // Returns highest index actually used
    virtual int					GetHighestEntityIndex(void) = 0;

    // Sizes entity list to specified size
    virtual void				SetMaxEntities(int maxents) = 0;
    virtual int					GetMaxEntities() = 0;
};


std::vector<CEntity*> getAllPlayers(bool enemiesOnly) {

    // storing all retured player entities in a vector

    std::vector<CEntity*> players;

    // looping through the entity list (did this many times in lua xd)

    const auto entityList = GetInterface<IClientEntityList>("VClientEntityList003", "client.dll");

    if (!entityList)
        return players;

    // in csgo indexes up to 64 are reserved for players only. So the loop below will only return player entities if there's any.
    for (auto i = 1; i <= 64; ++i) {
        const auto player = entityList->GetClientEntity(i);

        if (!player)
            continue;

        players.push_back(player);
    }

    return players;

}

// thread is always running

DWORD __stdcall Main(LPVOID lpvReserved) {
    AllocConsole();
    // freopen_s
    FILE* fileptr;

    // file double ptr cuz we used * to indicate fileptr is a FILE (type) pointer
    // & returns a pointer to the original var
    // our case is a file ptr so double ptr because ur referencing a ptr

    freopen_s(&fileptr, "CONOUT$", "w", stdout);
    std::cout << "PUNJABI SDK INJECTED"<<std::endl;

    // hack loop
    while (!GetAsyncKeyState(VK_END)) {

        if (GetAsyncKeyState(VK_INSERT) & 1) {
            std::vector<CEntity*> allPlayers = getAllPlayers(false);

            for (auto player : allPlayers) {
                int health = player->GetHealth();
                std::cout << "Player Index: " << "Health: " << health << "\n";

            }


            // cdazz how do I properly free memory for our players above ^^^? Can you fix this?



        }
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