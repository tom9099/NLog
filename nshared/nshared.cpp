#include "nshared.h"


#if NS_WINDOWS
#include <Windows.h>
#endif


NShared::NShared()
{
}

void NShared::boostPriority()
{
#if NS_WINDOWS
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
#endif
}
