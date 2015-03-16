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
    XSqlUser* sqlUser = sqlShop_->getSqlUser();
    return sqlUser->userExists(name);
}

bool XShop::userCheck(const std::string& name, const std::string& pwd)
{
    XSqlUser* sqlUser = sqlShop_->getSqlUser();
    return sqlUser->userCheck(name, pwd);
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
    XSqlColor* color = sqlShop_->getSqlColor();
    return color->addColor(xColorCard(rgb, card, name));
}

bool XShop::delColor(unsigned int card)
{
    XSqlColor* color = sqlShop_->getSqlColor();
    return color->delColor(card);
}

bool XShop::modifyColor(const xColorCard& cc)
{
    XSqlColor* color = sqlShop_->getSqlColor();
    return color->modifyColor(cc);
}

bool XShop::queryColor(lpxColorCardArray& arrColor)
{
    XSqlColor* color = sqlShop_->getSqlColor();
    return color->queryColor(arrColor);
}

