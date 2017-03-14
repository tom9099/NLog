#ifndef NSHARED_H
#define NSHARED_H

#include "nshared_global.h"

#define NS_FAIL_IF(cond, msg) do { if (cond) ns_fail_if(#cond, msg); } while (0)

class NSHAREDSHARED_EXPORT NShared
{

public:
    NShared();

    static void boostPriority();

};

#endif // NSHARED_H
