#include "IGuard.hpp"

// https://learn.microsoft.com/ru-ru/windows/win32/shell/csidl
// https://learn.microsoft.com/ru-ru/windows/win32/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath
// user folder - C:\Users\%USERNAME%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup
// all folder - C:\ProgramData\Microsoft\Windows\Start Menu\Programs\StartUp

class AutoStartFolderGuard final : public IGuard
{
public:
    AutoStartFolderGuard() = default;
};
