#include "nshared.h"


#if NS_WINDOWS
#include <Windows.h>
#elif NS_LINUX
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>
#endif


NShared::NShared()
{
}

void NShared::boostPriority()
{
#if NS_WINDOWS
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
#elif NS_LINUX
    int which = PRIO_PROCESS;
    setpriority(which, getpid(), -20);
#endif
}
