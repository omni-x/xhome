#include "xsqlColor.h"
#include "xsqlDef.h"
#include "./sqlite/CppSQLite3.h"

XSqlColor::XSqlColor(CppSQLite3DB* sqlite) : sqlite_(sqlite)
{

}

XSqlColor::~XSqlColor()
{

}

bool XSqlColor::addColor(const xColorCard& color)
{
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_COLOR_INSERT_XXX, color.card_, color.name_, color.rgb_);
    CppSQLite3Query q = sqlite_->execQuery(bufSQL);
    bool rc = q.eof();
    q.finalize();
    return rc;
}

bool XSqlColor::delColor(unsigned int card)
{
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_COLOR_DELETE_WHERE_CARD, card);
    CppSQLite3Query q = sqlite_->execQuery(bufSQL);
    bool rc = q.eof();
    q.finalize();
    return rc;
}

bool XSqlColor::modifyColor(const xColorCard& color)
{
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_COLOR_UPDATE_WHERE_ID, color.card_, color.name_, color.rgb_);
    CppSQLite3Query q = sqlite_->execQuery(bufSQL);
    bool rc = q.eof();
    q.finalize();
    return rc;
}

bool XSqlColor::queryColor(lpxColorCardArray& arrColor)
{   
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_COLOR_QUERY_ALL);
    CppSQLite3Query q = sqlite_->execQuery(bufSQL);
    bool rc = q.eof();
    while (!q.eof())
    {
        lpxColorCard color = new xColorCard;
        color->id_ = q.getIntField("id");
        color->card_ = q.getIntField("card");
        color->name_ = q.fieldValue("name");
        color->rgb_ = q.getIntField("rgb");
        arrColor.push_back(color);
        q.nextRow();
    }
    q.finalize();
    return rc;
}
