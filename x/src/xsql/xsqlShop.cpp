#include "xsqlShop.h"
#include "xsqlDef.h"
#include "../xscheme/xscheme.h"
#include "./sqlite/CppSQLite3.h"


#define Room_Living         "����"
#define Room_Dining         "����"
#define Room_Bed_1st        "����1"
#define Room_Bed_2nd        "����2"
#define Room_Bed_3rd        "����3"
#define Wall_Normal         "ǽ��"
#define Wall_TV             "����ǽ"
#define Wall_Sofa           "ɳ������ǽ"
#define Wall_CeilingBorder  "�컨���Ե"
#define Wall_Other          "����"


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
    sqlite_->execDML(X_SQL_USER_CREATE);            // ��-����Ա
    sqlite_->execDML(X_SQL_CUSTOMER_CREATE);        // ��-�ͻ�
    sqlite_->execDML(X_SQL_CUSTOMERGROUP_CREATE);   // ��-�ͻ�����
    sqlite_->execDML(X_SQL_MATERIALS_CREATE);       // ��-����
    sqlite_->execDML(X_SQL_USEOFMATERIALS_CREATE);  // ��-����
    sqlite_->execDML(X_SQL_COLOR_CREATE);           // ��-ɫ��

    sqlite_->execDML(X_SQL_ORDER_CREATE);           // ��-������
    sqlite_->execDML(X_SQL_DESIGNER_CREATE);        // ��-���ʦ

    sqlite_->execDML(X_SQL_ORDER_INSERT_CRAFTS);    // ����
    sqlite_->execDML(X_SQL_ORDER_INSERT_MODEL);     // �ͺ�
    sqlite_->execDML(X_SQL_ORDER_INSERT_BACKGROUND);// ��ɫ
    sqlite_->execDML(X_SQL_ORDER_INSERT_FACE);      // ��ɫ
    sqlite_->execDML(X_SQL_ORDER_INSERT_BOTTOM);    // ӡ����
    sqlite_->execDML(X_SQL_ORDER_INSERT_AREA);      // ���

    sqlite_->execDML(X_SQL_PLACE_CREATE);
    sqlite_->execDML(X_SQL_WALL_CREATE);

    sqlite_->execDML(X_SQL_USER_INSERT_ADMIN);      // ��ӹ���Ա

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
