#include "xsqlShop.h"
#include "xsqlDef.h"
#include "../xscheme/xscheme.h"
#include "./sqlite/CppSQLite3.h"


#define Room_Living         "客厅"
#define Room_Dining         "餐厅"
#define Room_Bed_1st        "主卧1"
#define Room_Bed_2nd        "次卧2"
#define Room_Bed_3rd        "次卧3"
#define Wall_Normal         "墙面"
#define Wall_TV             "电视墙"
#define Wall_Sofa           "沙发背景墙"
#define Wall_CeilingBorder  "天花板边缘"
#define Wall_Other          "其它"


XSqlShop::XSqlShop(const std::string& file) : file_(file) 
{
    sqlite_ = new CppSQLite3DB;
    user_ = new XSqlUser(sqlite_);
    color_ = new XSqlColor(sqlite_);
    order_ = new XSqlOrder(sqlite_);
    material_ = new XSqlMaterial(sqlite_);
    customer_ = new XSqlCustomer(sqlite_);
}

XSqlShop::~XSqlShop()
{
    SAFE_DELETE(customer_);
    SAFE_DELETE(material_);
    SAFE_DELETE(user_);
    SAFE_DELETE(color_);
    SAFE_DELETE(order_);
    SAFE_DELETE(sqlite_);
}


xError XSqlShop::createShop()
{
    assert(!file_.empty());
    
    sqlite_->open(file_.c_str());

    if ( !createShopTable() )
        return x_Failure;

    if ( !createDefaultData() )
        return x_Failure;

    return x_NoErr;
}

bool XSqlShop::createShopTable()
{
    sqlite_->execDML(X_SQL_USER_CREATE);            // 表-操作员
    sqlite_->execDML(X_SQL_CUSTOMER_CREATE);        // 表-客户
    sqlite_->execDML(X_SQL_CUSTOMERGROUP_CREATE);   // 表-客户分组
    sqlite_->execDML(X_SQL_MATERIALS_CREATE);       // 表-材料
    sqlite_->execDML(X_SQL_USEOFMATERIALS_CREATE);  // 表-用料
    sqlite_->execDML(X_SQL_COLOR_CREATE);           // 表-色卡

    sqlite_->execDML(X_SQL_ORDER_CREATE);           // 表-大区域
    sqlite_->execDML(X_SQL_DESIGNER_CREATE);        // 表-设计师

    sqlite_->execDML(X_SQL_ORDER_INSERT_CRAFTS);    // 工艺
    sqlite_->execDML(X_SQL_ORDER_INSERT_MODEL);     // 型号
    sqlite_->execDML(X_SQL_ORDER_INSERT_BACKGROUND);// 底色
    sqlite_->execDML(X_SQL_ORDER_INSERT_FACE);      // 面色
    sqlite_->execDML(X_SQL_ORDER_INSERT_BOTTOM);    // 印花底
    sqlite_->execDML(X_SQL_ORDER_INSERT_AREA);      // 面积

    sqlite_->execDML(X_SQL_PLACE_CREATE);
    sqlite_->execDML(X_SQL_WALL_CREATE);

    sqlite_->execDML(X_SQL_USER_INSERT_ADMIN);      // 添加管理员

    return true;
}

bool XSqlShop::createDefaultData()
{
    order_->addPlace(Room_Living);
    order_->addPlace(Room_Dining);
    order_->addPlace(Room_Bed_1st);
    order_->addPlace(Room_Bed_2nd);
    order_->addPlace(Room_Bed_3rd);
    order_->addWall(Wall_Normal);
    order_->addWall(Wall_TV);
    order_->addWall(Wall_Sofa);
    order_->addWall(Wall_CeilingBorder);
    order_->addWall(Wall_Other);

    return true;
}

xError XSqlShop::openShop()
{
    assert(!file_.empty());
    sqlite_->open(file_.c_str());
    return x_NoErr;
}

void XSqlShop::closeShop()
{
    return sqlite_->close();
}
