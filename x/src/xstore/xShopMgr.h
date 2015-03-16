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

protected:
    bool scanShop();

private:
    XShopArray  arrShop_;
};

#endif