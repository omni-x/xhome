#include "xsqlShop.h"
#include "xsqlDef.h"
#include "./sqlite/CppSQLite3.h"
#include "../xscheme/xscheme.h"


XSqlShop::XSqlShop(const std::string& file) : file_(file) 
{
    sqlite_ = new CppSQLite3DB;
}

XSqlShop::~XSqlShop()
{
    SAFE_DELETE(sqlite_);
}


xError XSqlShop::createShop()
{
    assert(!file_.empty());

    std::string tempfile = XPathMgr::instance().getDBPath();
    tempfile += file_;
    
    sqlite_->open(tempfile.c_str());

    sqlite_->execDML(X_SQL_USER_CREATE);
    sqlite_->execDML(X_SQL_USER_INSERT_ADMIN);
    sqlite_->execDML(X_SQL_CUSTOMER_CREATE);
    sqlite_->execDML(X_SQL_MATERIALS_CREATE);
    
    return x_NoErr;
}

xError XSqlShop::openShop()
{
    assert(!file_.empty());

    std::string tempfile = XPathMgr::instance().getDBPath();
    tempfile += file_;
    sqlite_->open(tempfile.c_str());

    return x_NoErr;
}

void XSqlShop::closeShop()
{
    return sqlite_->close();
}

bool XSqlShop::userExists(const std::string& name)
{
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_USER_QUERY_XXX, name.c_str());
    CppSQLite3Query q = sqlite_->execQuery(bufSQL);
    bool rc = q.eof();
    q.finalize();
    return rc;
}

bool XSqlShop::userCheck(const std::string& name, const std::string& pwd)
{
    bool rc = false;
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_USER_QUERY_XXX, name.c_str());
    CppSQLite3Query q = sqlite_->execQuery(bufSQL);
    if (!q.eof())
    {
        for (int fld = 0; fld < q.numFields(); fld++)
        {
            const char* lpwd = q.fieldValue("password");
            if ( strcmp(pwd.c_str(), lpwd) == 0 )
                rc = true;
        }
    }
    q.finalize();
    return rc;
}
