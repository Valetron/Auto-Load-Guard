//#include "RegistryGuard.hpp"
//#include "TaskSchedulerGuard.hpp"
#include "AutoStartFolderGuard.hpp"

int main(void)
{
    AutoStartFolderGuard a;
    a.run();
    return 0;
}
