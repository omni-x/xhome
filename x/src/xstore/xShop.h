#ifndef _xShop_h__
#define _xShop_h__

#include "xStorePre.h"
#include "../../include/xError.h"

class XSqlShop;
class _xstore_ XShop
{
public:
    XShop();
    ~XShop();

    xError install(const std::string& name);
    xError uninstall();
    xError open(const std::string name);
    void close();
    bool userExists(const std::string& name);
    bool userCheck(const std::string& name, const std::string& pwd);

public:
    XSqlShop* sqlShop_;
};

#endif