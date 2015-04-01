#include "xShop.h"
#include "../xsql/xsql.h"
#include "../xscheme/xscheme.h"

XShop::XShop() : sqlShop_(NULL)
{

}

XShop::~XShop()
{
    SAFE_DELETE(sqlShop_);
}


xError XShop::install(const std::string& file)
{
    std::string tempfile = XPathMgr::instance().getDBPath();
    tempfile += file;
    tempfile += X_FILE_EXT;
    sqlShop_ = new XSqlShop(tempfile);
    return sqlShop_->createShop();
}

xError XShop::uninstall()
{
    return x_NoErr;
}

bool XShop::userExists(const std::string& name)
{
    XSqlUser* sql = sqlShop_->getSqlUser();
    return sql->userExists(name);
}

bool XShop::userCheck(const std::string& name, const std::string& pwd)
{
    XSqlUser* sql = sqlShop_->getSqlUser();
    return sql->userCheck(name, pwd);
}

xError XShop::open(const std::string& file)
{
    sqlShop_ = new XSqlShop(file);
    return sqlShop_->openShop();
}

void XShop::close()
{
    return sqlShop_->closeShop();
}

bool XShop::addColor(unsigned int card, const std::string& name, unsigned int rgb)
{
    XSqlColor* sql = sqlShop_->getSqlColor();
    return sql->addColor(xColorCard(rgb, card, name));
}

bool XShop::delColor(unsigned int card)
{
    XSqlColor* sql = sqlShop_->getSqlColor();
    return sql->delColor(card);
}

bool XShop::modifyColor(const xColorCard& cc)
{
    XSqlColor* sql = sqlShop_->getSqlColor();
    return sql->modifyColor(cc);
}

bool XShop::queryColor(lpxColorCardArray& arrColor)
{
    XSqlColor* sql = sqlShop_->getSqlColor();
    return sql->queryColor(arrColor);
}

bool XShop::addCustomer(xCustomer& customer)
{
    XSqlCustomer* sql = sqlShop_->getSqlCustomer();
    return sql->addCustomer(customer);
}

bool XShop::getCustomer(lpxCustomerArray& arrCustomer)
{
    XSqlCustomer* sql = sqlShop_->getSqlCustomer();
    return sql->getCustomer(arrCustomer);
}
