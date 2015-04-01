#include "xsqlCustomer.h"
#include "xsqlDef.h"
#include "./sqlite/CppSQLite3.h"

XSqlCustomer::XSqlCustomer(CppSQLite3DB* sqlite) : sqlite_(sqlite)
{

}

XSqlCustomer::~XSqlCustomer()
{

}

bool XSqlCustomer::customerExists(const std::string& name)
{
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_CUSTOMER_QUERY_XXX, name.c_str());
    CppSQLite3Query q = sqlite_->execQuery(bufSQL);
    bool rc = q.eof();
    q.finalize();
    return rc;
}

bool XSqlCustomer::getCustomer(lpxCustomerArray& arrCustomer)
{
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_CUSTOMER_QUERY_ALL);
    CppSQLite3Query q = sqlite_->execQuery(bufSQL);
    bool rc = q.eof();
    while (!q.eof())
    {
        lpxCustomer customer = new xCustomer;
        customer->id_ = q.getIntField("id");
        customer->Tel_ = q.fieldValue("tel");
        customer->name_ = q.fieldValue("name");
        customer->QQ_ = q.fieldValue("qq");
        arrCustomer.push_back(customer);
        q.nextRow();
    }
    q.finalize();
    return rc;
}

bool XSqlCustomer::addCustomer(xCustomer& customer)
{
    bool rc = false;
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_CUSTOMER_INSERT_XXX, customer.name_.c_str(), customer.Tel_.c_str(), customer.QQ_.c_str());
    sqlite_->execQuery(bufSQL);
    bufSQL.clear();
    bufSQL.format(X_SQL_CUSTOMER_QUERY_NAME, customer.name_.c_str());
    CppSQLite3Query q = sqlite_->execQuery(bufSQL);
    while (!q.eof())
    {
        customer.id_ = q.getIntField("id");
        q.nextRow();
    }
    q.finalize();
    return true;
}

bool XSqlCustomer::delCustomer(const std::string& name)
{
    bool rc = false;
    CppSQLite3Buffer bufSQL;
    bufSQL.format(X_SQL_CUSTOMER_DELETE_NAME, name.c_str());
    sqlite_->execQuery(bufSQL);
    return true;
}

