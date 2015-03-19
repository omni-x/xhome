#ifndef _xsqlOrder_h__
#define _xsqlOrder_h__


#include "xsqlPre.h"
#include "../../include/xError.h"
#include "../../include/xOrder.h"

class CppSQLite3DB;
class _xsql_ XSqlOrder
{
public: 
    XSqlOrder(CppSQLite3DB* sqlite);
    ~XSqlOrder();

    bool addPlace(const std::string& name);
    bool addWall(const std::string& name);

private:
    CppSQLite3DB*   sqlite_;
};

#endif