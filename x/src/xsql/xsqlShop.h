#ifndef _xsqlShop_h__
#define _xsqlShop_h__

#include "xsqlPre.h"
#include "../../include/xError.h"

class _xsql_ XSqlShop
{
public: 
    XSqlShop(const std::string& name);
    ~XSqlShop();
    xError createShop();

private:
    std::string name_;
};

#endif