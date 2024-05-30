#include <winnt.h>

#include "IGuard.hpp"

// https://learn.microsoft.com/ru-ru/windows/win32/api/winreg/nf-winreg-regnotifychangekeyvalue
// https://learn.microsoft.com/en-us/windows/win32/setupapi/run-and-runonce-registry-keys

class RegistryGuard final : public IGuard
{
public:
    RegistryGuard() = default;
    void compareState() override;

private:
    void init();

private:
    constexpr DWORD M_NOTIFY_FILTER_FLAGS = REG_NOTIFY_CHANGE_NAME
                                            | REG_NOTIFY_CHANGE_ATTRIBUTES
                                            | REG_NOTIFY_CHANGE_LAST_SET
                                            | REG_NOTIFY_CHANGE_SECURITY;
};
