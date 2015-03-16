#include "xsqlShop.h"
#include "xsqlDef.h"
#include "../xscheme/xscheme.h"
#include "./sqlite/CppSQLite3.h"


XSqlShop::XSqlShop(const std::string& file) : file_(file) 
{
    sqlite_ = new CppSQLite3DB;
    user_ = new XSqlUser(sqlite_);
    color_ = new XSqlColor(sqlite_);
}

XSqlShop::~XSqlShop()
{
    SAFE_DELETE(sqlite_);
}


xError XSqlShop::createShop()
{
    assert(!file_.empty());
    
    sqlite_->open(file_.c_str());

    sqlite_->execDML(X_SQL_USER_CREATE);
    sqlite_->execDML(X_SQL_USER_INSERT_ADMIN);
    sqlite_->execDML(X_SQL_CUSTOMER_CREATE);
    sqlite_->execDML(X_SQL_MATERIALS_CREATE);
    sqlite_->execDML(X_SQL_COLOR_CREATE);   
   
    return x_NoErr;
}

xError XSqlShop::openShop()
{
    assert(!file_.empty());
    sqlite_->open(file_.c_str());
    return x_NoErr;
}

void XSqlShop::closeShop()
{
    return sqlite_->close();
}
