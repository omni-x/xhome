#include "xShop.h"
#include "../xsql/xsql.h"

XShop::XShop() : sqlShop_(NULL)
{

}

XShop::~XShop()
{
    SAFE_DELETE(sqlShop_);
}


xError XShop::install(const std::string& name)
{
    std::string file = name + X_FILE_EXT;
    sqlShop_ = new XSqlShop(file);
    return sqlShop_->createShop();
}

xError XShop::uninstall()
{
    return x_NoErr;
}

bool XShop::userExists(const std::string& name)
{
    return sqlShop_->userExists(name);
}

bool XShop::userCheck(const std::string& name, const std::string& pwd)
{
    return sqlShop_->userCheck(name, pwd);
}

xError XShop::open(const std::string name)
{
    std::string file = name + X_FILE_EXT;
    sqlShop_ = new XSqlShop(file);
    return sqlShop_->openShop();
}

void XShop::close()
{
    return sqlShop_->closeShop();
}
