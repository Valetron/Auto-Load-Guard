#include <string>
#include <filesystem>
#include <unordered_map>

#include "IGuard.hpp"

// https://learn.microsoft.com/ru-ru/windows/win32/shell/csidl
// https://learn.microsoft.com/ru-ru/windows/win32/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath
// user folder - C:\Users\%USERNAME%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup
// all folder - C:\ProgramData\Microsoft\Windows\Start Menu\Programs\StartUp

namespace fs = std::filesystem;

class AutoStartFolderGuard final : public IGuard
{
public:
    AutoStartFolderGuard();
    void compareState() override;
    void run() override;

private:
    void init();

private:
    fs::path m_userAutoStartFolderPath;
    fs::path m_allAutoStartFolderPath;
    std::unordered_map<std::wstring, std::wstring> m_filePath;
};
