#ifndef _xRoot_h__
#define _xRoot_h__

#include "../../include/xError.h"
#include "xlogicPre.h"

class XShopMgr;
class _xlogic_ XRoot
{
public:
    XRoot();
    ~XRoot();

public:
    void init();
    void uninit();

    XShopMgr*   getShopMgr();

private:
    XShopMgr*   shopmgr_;
};

inline XShopMgr* XRoot::getShopMgr()
{
    return shopmgr_;
}

#endif
