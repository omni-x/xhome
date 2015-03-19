#ifndef _xsqlShop_h__
#define _xsqlShop_h__

#include "xsqlPre.h"
#include "../../include/xError.h"
#include "xsqlUser.h"
#include "xsqlColor.h"
#include "xsqlOrder.h"

class CppSQLite3DB;
class _xsql_ XSqlShop
{
public: 
    XSqlShop(const std::string& file);
    ~XSqlShop();
    xError createShop();
    xError openShop();
    void closeShop();

    XSqlUser* getSqlUser();
    XSqlColor* getSqlColor();
    XSqlOrder*  getSqlOrder();

protected:
    bool createShopTable();
    bool createDefaultData();

private:
    std::string     file_;
    CppSQLite3DB*   sqlite_;
    XSqlUser*       user_;
    XSqlColor*      color_;
    XSqlOrder*      order_;
};

inline XSqlUser* XSqlShop::getSqlUser()
{
    return user_;
}

inline XSqlColor* XSqlShop::getSqlColor()
{
    return color_;
}

inline XSqlOrder* XSqlShop::getSqlOrder()
{
    return order_;
}

#endif