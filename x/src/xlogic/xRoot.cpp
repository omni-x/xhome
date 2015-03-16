#include "xRoot.h"
#include "../xstore/xstore.h"

XRoot::XRoot() : shopmgr_(NULL)
{

}

XRoot::~XRoot()
{

}

void XRoot::init()
{
    shopmgr_ = new XShopMgr;
    shopmgr_->init();
}

void XRoot::uninit()
{
    shopmgr_->uninit();
    SAFE_DELETE(shopmgr_);
}
