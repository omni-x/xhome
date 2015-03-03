#ifndef _xsqlShop_h__
#define _xsqlShop_h__

#include "xsqlPre.h"
#include "../../include/xError.h"

class CppSQLite3DB;
class _xsql_ XSqlShop
{
public: 
    XSqlShop(const std::string& file);
    ~XSqlShop();
    xError createShop();
    xError openShop();
    void closeShop();
    bool userExists(const std::string& name);
    bool userCheck(const std::string& name, const std::string& pwd);

private:
    std::string     file_;
    CppSQLite3DB*   sqlite_;
};

#endif