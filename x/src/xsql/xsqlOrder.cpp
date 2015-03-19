#include "xsqlOrder.h"
#include "xsqlDef.h"
#include "./sqlite/CppSQLite3.h"


XSqlOrder::XSqlOrder(CppSQLite3DB* sqlite) : sqlite_(sqlite)
{

}

XSqlOrder::~XSqlOrder()
{

}

bool XSqlOrder::addPlace(const std::string& name)
{
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_PLACE_INSERT_XXX, name);
    CppSQLite3Query q = sqlite_->execQuery(bufSQL);
    bool rc = q.eof();
    q.finalize();
    return rc;
}

bool XSqlOrder::addWall(const std::string& name)
{
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_WALL_INSERT_XXX, name);
    CppSQLite3Query q = sqlite_->execQuery(bufSQL);
    bool rc = q.eof();
    q.finalize();
    return rc;
}
