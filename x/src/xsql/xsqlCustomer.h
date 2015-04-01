#ifndef _xsqlCustomer_h__
#define _xsqlCustomer_h__


#include "xsqlPre.h"
#include "../../include/xError.h"
#include "../../include/xCustomer.h"

class CppSQLite3DB;
class _xsql_ XSqlCustomer
{
public: 
    XSqlCustomer(CppSQLite3DB* sqlite);
    ~XSqlCustomer();

    bool customerExists(const std::string& name);
    bool getCustomer(lpxCustomerArray& arrCustomer);
    bool addCustomer(xCustomer& customer);
    bool delCustomer(const std::string& name);

private:
    CppSQLite3DB*   sqlite_;
};


#endif