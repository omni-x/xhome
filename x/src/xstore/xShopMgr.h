#ifndef _xShopMgr_h__
#define _xShopMgr_h__

#include "../../include/xError.h"
#include "xstorePre.h"

class XShop;
class _xstore_ XShopMgr
{
public:
    XShopMgr();
    ~XShopMgr();

    xError init();
    xError uninit();
    int getShopCount();
    XShop* newShop();
    void delShop(XShop* shop);
};

#endif