#ifndef _xRoot_h__
#define _xRoot_h__

#include "../../include/xError.h"
#include "xlogicPre.h"

class XLogin;
class XShopMgr;
class _xlogic_ XRoot
{
public:
    XRoot();
    ~XRoot();

public:
    void init();
    void uninit();

    XLogin*     getLogin();
    XShopMgr*   getShopMgr();

private:
    XLogin*     login_;
    XShopMgr*   shopmgr_;
};

inline XLogin* XRoot::getLogin()
{
    return login_;
}

inline XShopMgr* XRoot::getShopMgr()
{
    return shopmgr_;
}

#endif
