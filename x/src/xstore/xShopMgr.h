#ifndef _xShopMgr_h__
#define _xShopMgr_h__

#include "../../include/xError.h"
#include "xstorePre.h"
#include "xShop.h"

class _xstore_ XShopMgr
{
public:
    XShopMgr();
    ~XShopMgr();

    xError init();
    xError uninit();
    unsigned int getShopCount();
    XShop* newShop();
    void delShop(XShop* shop);
    XShop* curShop();
    void curShop(XShop* shop);

protected:
    bool scanShop();

private:
    XShopArray  arrShop_;
    XShop*      curShop_;
};

inline XShop* XShopMgr::curShop()
{
    return curShop_;
}

#endif