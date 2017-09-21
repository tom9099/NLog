#ifndef NSHARED_CONFIG_H_
#define NSHARED_CONFIG_H_

#include "nshared_global.h"

#include "xml/rapidxml.hpp"
#include "xml/rapidxml_iterators.hpp"
#include "xml/rapidxml_print.hpp"
#include "xml/rapidxml_utils.hpp"

class NConfig
{

    NS_NONCOPYABLE(NConfig)

protected:

    void loadDefault();

public:

    void init();
    void save();

};

#endif /*NSHARED_CONFIG_H_*/
