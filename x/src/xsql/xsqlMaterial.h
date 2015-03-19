#ifndef _xsqlMaterial_h__
#define _xsqlMaterial_h__


#include "xsqlPre.h"
#include "../../include/xError.h"
#include "../../include/xMaterial.h"

class CppSQLite3DB;
class _xsql_ XSqlMaterial
{
public: 
    XSqlMaterial(CppSQLite3DB* sqlite);
    ~XSqlMaterial();

    bool addMaterial(const std::string& name, unsigned int color, double weight);
    bool deleteMaterial(unsigned int id);
    bool updateMaterial(lpxMaterial material);
    bool updateMaterial(unsigned int id, double weight);
    bool queryMaterial(lpxMaterialArray& materialArray);

private:
    CppSQLite3DB*   sqlite_;
};


#endif