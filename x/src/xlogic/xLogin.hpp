#ifndef _xlogin_h__
#define _xlogin_h__

#include "../../include/xError.h"
#include "xlogicPre.h"

class XLogin
{
public:
    XLogin()
    {

    }
    ~XLogin()
    {

    }
    xError login(const std::string& user, const std::string& pwd)
    {
        return x_NoErr;
    }
};

#endif