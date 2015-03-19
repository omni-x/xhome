#pragma once
#include "../../../include/xCustomer.h"

class CCustomerMgr
{
public:
    CCustomerMgr();
    ~CCustomerMgr();

public:
    bool Add(lpxCustomer pxCustomer);
    bool DelCustomer(unsigned int iID);
    const lpxCustomer GetCustomer(unsigned int iCustomerID);
    const lpxCustomerArray& GetCustomers();

    const lpxCustomerGroupArray& GetGroups();
    const lpxCustomerGroup GetGroup(unsigned int iGroupID);
public:
    void    Load();
    void    Save();

protected:
    void    CheckGroups();

protected:
    lpxCustomerArray        m_arrCustomer;
    lpxCustomerGroupArray   m_arrGroups;
};