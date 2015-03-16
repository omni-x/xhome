#ifndef _xsqlUser_h__ 
#define _xsqlUser_h__ 

#include "xsqlPre.h"
#include "../../include/xError.h"

class CppSQLite3DB;
class _xsql_ XSqlUser
{
public: 
    XSqlUser(CppSQLite3DB* sqlite);
    ~XSqlUser();

    bool userExists(const std::string& name);
    bool userCheck(const std::string& name, const std::string& pwd);

private:
    CppSQLite3DB*   sqlite_;
};

#endif