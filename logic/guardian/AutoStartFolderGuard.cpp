#include <iostream>

extern "C"
{
//#include <KnownFolders.h>
#include <shlobj_core.h>
}

#include "AutoStartFolderGuard.hpp"

AutoStartFolderGuard::AutoStartFolderGuard()
{
    init();
}

void AutoStartFolderGuard::init()
{
    if (S_OK != SHGetKnownFolderPath(FOLDERID_CommonStartup, KF_FLAG_DEFAULT, NULL, &m_allAutoStartFolderPath))
    {
        std::cerr << "Error\n";
        return;
    }

    if (S_OK != SHGetKnownFolderPath(FOLDERID_Startup, KF_FLAG_DEFAULT, NULL, &m_userAutoStartFolderPath))
    {
        std::cerr << "Error\n";
        return;
    }
}

void AutoStartFolderGuard::compareState()
{
    ;
}
