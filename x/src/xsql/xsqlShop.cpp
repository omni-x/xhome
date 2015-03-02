#include "xsqlShop.h"
#include "xsqlDef.h"
#include "./sqlite/CppSQLite3.h"
#include "../xscheme/xscheme.h"

XSqlShop::XSqlShop(const std::string& name) : name_(name) 
{

}

XSqlShop::~XSqlShop()
{

}


xError XSqlShop::createShop()
{
    assert(!name_.empty());

    std::string file = XPathMgr::instance().getDBPath();
    file += name_;
    file += ".sqlite";
    
    CppSQLite3DB sqlite;
    sqlite.open(file.c_str());

    sqlite.execDML(X_SQL_CREATE_USER);
    sqlite.execDML(X_SQL_INSERT_ADMIN);

    return x_NoErr;
}
