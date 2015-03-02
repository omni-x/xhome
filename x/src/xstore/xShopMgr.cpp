#include "xShopMgr.h"
#include "xShop.h"


XShopMgr::XShopMgr()
{

}

XShopMgr::~XShopMgr()
{

}

xError XShopMgr::init()
{
    return x_NoErr;
}

xError XShopMgr::uninit()
{
    return x_NoErr;
}

int XShopMgr::getShopCount()
{
    return 0;
}

XShop* XShopMgr::newShop()
{
    return new XShop;
}

void XShopMgr::delShop(XShop* shop)
{
    if (shop != NULL)
        delete shop;
}

