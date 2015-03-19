#include "xsqlMaterial.h"
#include "xsqlDef.h"
#include "./sqlite/CppSQLite3.h"


XSqlMaterial::XSqlMaterial(CppSQLite3DB* sqlite) : sqlite_(sqlite) 
{

}

XSqlMaterial::~XSqlMaterial()
{

}

bool XSqlMaterial::addMaterial(const std::string& name, unsigned int color, double weight)
{
    bool rc = false;
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_MATERIALS_INSERT_XXX, name.c_str(), color, weight);
    sqlite_->execQuery(bufSQL);
    return true;
}

bool XSqlMaterial::updateMaterial(lpxMaterial material)
{
    bool rc = false;
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_MATERIALS_UPDATE_WHERE_ID, 
        material->name_.c_str(), material->color_, material->weight_, material->id_);
    sqlite_->execQuery(bufSQL);
    return true;
}

bool XSqlMaterial::updateMaterial(unsigned int id, double weight)
{
    bool rc = false;
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_MATERIALS_UPDATE_WEIGHT_WHERE_ID, weight, id);
    sqlite_->execQuery(bufSQL);
    return true;
}

bool XSqlMaterial::deleteMaterial(unsigned int id)
{
    bool rc = false;
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_MATERIALS_DELETE_WHERE_ID, id);
    sqlite_->execQuery(bufSQL);
    return true;
}

bool XSqlMaterial::queryMaterial(lpxMaterialArray& materialArray)
{
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_MATERIALS_QUERY_ALL);
    CppSQLite3Query q = sqlite_->execQuery(bufSQL);
    bool rc = q.eof();
    while (!q.eof())
    {
        lpxMaterial color = new xMaterial(  q.getIntField("id"), 
                                            q.fieldValue("name"), 
                                            q.getIntField("color"), 
                                            q.getIntField("weight") );
        materialArray.push_back(color);
        q.nextRow();
    }
    q.finalize();
    return rc;
}
