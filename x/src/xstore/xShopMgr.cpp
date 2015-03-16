#include "xShopMgr.h"
#include "../xscheme/xscheme.h"

XShopMgr::XShopMgr()
{

}

XShopMgr::~XShopMgr()
{

}

xError XShopMgr::init()
{
    scanShop();
    return x_NoErr;
}

bool XShopMgr::scanShop()
{
    std::string tempfile = XPathMgr::instance().getDBPath();
    tempfile += "*";
    tempfile += X_FILE_EXT;

    _finddata_t fileInfo;
    long handle = _findfirst(tempfile.c_str(), &fileInfo);
    if (handle == -1L)
    {
        return false;
    }
    do 
    {
        XShop* shop = new XShop;
        if (x_NoErr == shop->open(fileInfo.name))
            arrShop_.push_back(shop);
        else
            SAFE_DELETE(shop);
    } while (_findnext(handle, &fileInfo) == 0);

    return true;
}

xError XShopMgr::uninit()
{
    return x_NoErr;
}

unsigned int XShopMgr::getShopCount()
{
    return arrShop_.size();
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

