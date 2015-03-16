#include "xsqlUser.h"
#include "xsqlDef.h"
#include "./sqlite/CppSQLite3.h"

XSqlUser::XSqlUser(CppSQLite3DB* sqlite) : sqlite_(sqlite)
{

}

XSqlUser::~XSqlUser()
{

}

bool XSqlUser::userExists(const std::string& name)
{
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_USER_QUERY_XXX, name.c_str());
    CppSQLite3Query q = sqlite_->execQuery(bufSQL);
    bool rc = q.eof();
    q.finalize();
    return rc;
}

bool XSqlUser::userCheck(const std::string& name, const std::string& pwd)
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
