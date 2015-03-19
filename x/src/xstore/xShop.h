#ifndef _xShop_h__
#define _xShop_h__

#include "xStorePre.h"
#include "../../include/xError.h"
#include "../../include/xCustomer.h"
#include "../../include/xMaterial.h"

class XSqlShop;
class _xstore_ XShop
{
public:
    XShop();
    ~XShop();

    xError install(const std::string& file);
    xError uninstall();
    xError open(const std::string& file);
    void close();
    bool userExists(const std::string& name);
    bool userCheck(const std::string& name, const std::string& pwd);
    bool addColor(unsigned int card, const std::string& name, unsigned int rgb);
    bool delColor(unsigned int card);
    bool modifyColor(const xColorCard& color);
    bool queryColor(lpxColorCardArray& arrColor);

private:
    XSqlShop* sqlShop_;
};

typedef std::vector<XShop*> XShopArray;

#endif