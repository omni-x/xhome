#ifndef _xlogin_h__
#define _xlogin_h__

#include "../../include/xError.h"
#include "xlogicPre.h"

class _xlogic_ XLogin
{
public:
    XLogin();
    ~XLogin();
    xError login(const std::string& user, const std::string& pwd);
};

#endif