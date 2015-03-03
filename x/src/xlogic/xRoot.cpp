#include "xRoot.h"
#include "../xstore/xstore.h"
#include "xLogin.h"

XRoot::XRoot() : login_(NULL), shopmgr_(NULL)
{

}

XRoot::~XRoot()
{

}

void XRoot::init()
{
    login_ = new XLogin;
    shopmgr_ = new XShopMgr;
    shopmgr_->init();
}

void XRoot::uninit()
{
    shopmgr_->uninit();

    SAFE_DELETE(shopmgr_);
    SAFE_DELETE(login_);
}
