#ifndef _xsqlColor_h__
#define _xsqlColor_h__


#include "xsqlPre.h"
#include "../../include/xError.h"
#include "../../include/xMaterial.h"

class CppSQLite3DB;
class _xsql_ XSqlColor
{
public: 
    XSqlColor(CppSQLite3DB* sqlite);
    ~XSqlColor();

    bool addColor(const xColorCard& color);
    bool delColor(unsigned int card);
    bool modifyColor(const xColorCard& color);
    bool queryColor(lpxColorCardArray& arrColor);

private:
    CppSQLite3DB*   sqlite_;
};


#endif