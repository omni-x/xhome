#include "xShop.h"
#include "../xsql/xsql.h"

XShop::XShop() : sqlShop_(NULL)
{

}

XShop::~XShop()
{

}


xError XShop::install(const std::string& name)
{
    sqlShop_ = new XSqlShop(name);
    return sqlShop_->createShop();
}

xError XShop::uninstall()
{
    return x_NoErr;
}

