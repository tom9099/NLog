#include "nshared.h"
#include <QString>


#if NS_WINDOWS
#include <Windows.h>
#elif NS_LINUX
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>
#endif

void ns_fail_if(QString cond, QString msg)
{
    MessageBoxA(0, (cond + QString(" ") + msg).toStdString().c_str(), "Error", MB_OK);
    TerminateProcess(GetCurrentProcess(), 0);
}

NShared::NShared()
{
}

void NShared::boostPriority()
{
    //NS_FAIL_IF(true, "error...");

#if NS_WINDOWS
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
#elif NS_LINUX
    int which = PRIO_PROCESS;
    setpriority(which, getpid(), -20);
#endif
}
