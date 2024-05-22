#include "IGuard.hpp"

// https://learn.microsoft.com/ru-ru/windows/win32/shell/csidl

class AutoStartFolderGuard final : public IGuard
{
public:
    AutoStartFolderGuard() = default;
};
