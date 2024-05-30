#include <windows.h>
#include <tchar.h>
#include <stdio.h>

//void main(int argc, char *argv[])
void __cdecl _tmain(int argc, TCHAR *argv[])
{
    DWORD  dwFilter = REG_NOTIFY_CHANGE_NAME |
                     REG_NOTIFY_CHANGE_ATTRIBUTES |
                     REG_NOTIFY_CHANGE_LAST_SET |
                     REG_NOTIFY_CHANGE_SECURITY;

    HANDLE hEvent;
    HKEY   hMainKey = HKEY_CURRENT_USER;
    HKEY   hKey;
    LONG   lErrorCode;

    // Display the usage error message.
//    if (argc != 3)
//    {
//        _tprintf(TEXT("Usage: notify [HKLM|HKU|HKCU|HKCR|HCC] [<subkey>]\n"));
//        return;
//    }

    // Open a key.
    lErrorCode = RegOpenKeyEx(hMainKey, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_NOTIFY, &hKey);
    if (lErrorCode != ERROR_SUCCESS)
    {
        _tprintf(TEXT("Error in RegOpenKeyEx (%d).\n"), lErrorCode);
        return;
    }

    // Create an event.
    hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (hEvent == NULL)
    {
        _tprintf(TEXT("Error in CreateEvent (%d).\n"), GetLastError());
        return;
    }

    // Watch the registry key for a change of value.
    lErrorCode = RegNotifyChangeKeyValue(hKey,
                                         TRUE,
                                         dwFilter,
                                         hEvent,
                                         TRUE);
    if (lErrorCode != ERROR_SUCCESS)
    {
        _tprintf(TEXT("Error in RegNotifyChangeKeyValue (%d).\n"), lErrorCode);
        return;
    }

    // Wait for an event to occur.
    _tprintf(TEXT("Waiting for a change in the specified key...\n"));
    if (WaitForSingleObject(hEvent, INFINITE) == WAIT_FAILED)
    {
        _tprintf(TEXT("Error in WaitForSingleObject (%d).\n"), GetLastError());
        return;
    }
    else
    {
        MessageBox(nullptr, "Change occured", "Title", MB_ICONWARNING | MB_YESNO | MB_SETFOREGROUND);
//        _tprintf(TEXT("\nChange has occurred.\n"));
    }

    // Close the key.
    lErrorCode = RegCloseKey(hKey);
    if (lErrorCode != ERROR_SUCCESS)
    {
        _tprintf(TEXT("Error in RegCloseKey (%d).\n"), GetLastError());
        return;
    }

    // Close the handle.
    if (!CloseHandle(hEvent))
    {
        _tprintf(TEXT("Error in CloseHandle.\n"));
        return;
    }
}
