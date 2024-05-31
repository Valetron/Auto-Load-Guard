#include <Windows.h>
#include <iostream>

void MonitorRegistryKey(HKEY hKey, LPCTSTR lpSubKey)
{
    DWORD dwFilter = REG_NOTIFY_CHANGE_NAME |
                     REG_NOTIFY_CHANGE_ATTRIBUTES |
                     REG_NOTIFY_CHANGE_LAST_SET |
                     REG_NOTIFY_CHANGE_SECURITY;
    HANDLE hEvent;
    LONG lResult;

    hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (hEvent == NULL)
    {
        std::cerr << "Error creating event" << std::endl;
        return;
    }

    lResult = RegNotifyChangeKeyValue(hKey, TRUE, dwFilter, hEvent, TRUE);
    if (lResult != ERROR_SUCCESS)
    {
        std::cerr << "Error setting up registry key notification" << std::endl;
        return;
    }

    while (true)
    {
        if (WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0)
        {
            std::cout << "Registry key has changed" << std::endl;

            // Re-enable notification for next change
            lResult = RegNotifyChangeKeyValue(hKey, TRUE, dwFilter, hEvent, TRUE);
            if (lResult != ERROR_SUCCESS)
            {
                std::cerr << "Error setting up registry key notification" << std::endl;
                return;
            }
        }
    }

    CloseHandle(hEvent);
}

int main()
{
    HKEY hKey;
    LONG lResult;

    lResult = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_NOTIFY, &hKey);
    if (lResult != ERROR_SUCCESS)
    {
        std::cerr << "Error opening registry key" << std::endl;
        return 1;
    }

    MonitorRegistryKey(hKey, TEXT("MyApp"));

    RegCloseKey(hKey);

    return 0;
}
