#include <iostream>

extern "C"
{
#include <Windows.h>
#include <shlobj_core.h>
}

#include "AutoStartFolderGuard.hpp"

AutoStartFolderGuard::AutoStartFolderGuard()
{
    init();
}

void AutoStartFolderGuard::init()
{
    PWSTR autoStartFolderPath {nullptr};
    if (S_OK != SHGetKnownFolderPath(FOLDERID_CommonStartup, KF_FLAG_DEFAULT, NULL, &autoStartFolderPath))
    {
        std::cerr << "Error\n";
        return;
    }
    m_allAutoStartFolderPath = autoStartFolderPath;

    PWSTR userAutoStartFolderPath {nullptr};
    if (S_OK != SHGetKnownFolderPath(FOLDERID_Startup, KF_FLAG_DEFAULT, NULL, &userAutoStartFolderPath))
    {
        std::cerr << "Error\n";
        return;
    }
    m_userAutoStartFolderPath = userAutoStartFolderPath;
}

void AutoStartFolderGuard::compareState()
{
    ;
}

void AutoStartFolderGuard::run()
{
    fs::recursive_directory_iterator iter {m_allAutoStartFolderPath};

    for (const auto& entry : iter)
    {
        std::cout << entry.path() << "\n";
    }

    fs::recursive_directory_iterator iter2 {m_userAutoStartFolderPath};

    for (const auto& entry : iter2)
    {
        const auto path = entry.path().remove_filename().string();
        const auto filename = entry.path().filename();
        std::cout << filename << ", " << path << "\n";
    }

//    fs::path
////    while (true)
//    {
//        fs::
//    }
}
