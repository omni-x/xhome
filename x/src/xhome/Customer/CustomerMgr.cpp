#include "stdafx.h"
#include "CustomerMgr.h"

class __FindGroupByID
{  
public:   
    __FindGroupByID(unsigned int id_)
    {
        iID = id_;
    }
    unsigned int iID;
    bool operator () (lpxCustomerGroup pGroup)
    {  

        return (pGroup->id_ == iID) ? true:false;       
    }  
};

class __FindCustomerByID
{  
public:   
    __FindCustomerByID(unsigned int id_)
    {
        iID = id_;
    }
    unsigned int iID;
    bool operator () (lpxCustomer pCustomer)
    {  

        return (pCustomer->id_ == iID) ? true:false;       
    }  
};

CCustomerMgr::CCustomerMgr()
{

}

CCustomerMgr::~CCustomerMgr()
{

}


bool CCustomerMgr::Add(lpxCustomer pxCustomer)
{
    if( pxCustomer == NULL )
        return false;

    m_arrCustomer.push_back(pxCustomer);

    //do whith db
    //...

    return true;
}

bool CCustomerMgr::DelCustomer(unsigned int iID)
{
    lpxCustomerArray::iterator itor = m_arrCustomer.end();
    __FindCustomerByID _Finder(iID);
    itor = find_if(m_arrCustomer.begin(),m_arrCustomer.end(),_Finder);

    if( itor != m_arrCustomer.end() )
    {
        //do whith db
        //...

        m_arrCustomer.erase(itor);

        return true;
    }

    return false;
}


const lpxCustomerArray& CCustomerMgr::GetCustomers()
{
    return m_arrCustomer;
}

const lpxCustomer CCustomerMgr::GetCustomer(unsigned int iCustomerID)
{
    lpxCustomerArray::iterator itor = m_arrCustomer.end();
    __FindCustomerByID _Finder(iCustomerID);
    itor = find_if(m_arrCustomer.begin(),m_arrCustomer.end(),_Finder);

    if( itor != m_arrCustomer.end() )
        return *itor;

    return NULL;
}

void CCustomerMgr::Load()
{
    for(int i = 0; i < 10; i++)
    {
        CString strTemp;
        strTemp.Format(_T("customer%d"),i);
        xCustomer* pCustomer = new xCustomer;
        pCustomer->name_ = strTemp;
        pCustomer->id_ = i;
        pCustomer->Tel_ = strTemp;
        pCustomer->QQ_ = strTemp;
        m_arrCustomer.push_back(pCustomer);            
    }
}

void CCustomerMgr::Save()
{

}

const lpxCustomerGroupArray& CCustomerMgr::GetGroups()
{
    return m_arrGroups;
}

const lpxCustomerGroup CCustomerMgr::GetGroup(unsigned int iGroupID)
{
      lpxCustomerGroupArray::iterator itor = m_arrGroups.end();
      __FindGroupByID _Finder(iGroupID);
      itor = find_if(m_arrGroups.begin(),m_arrGroups.end(),_Finder);
    
      if( itor != m_arrGroups.end() )
          return *itor;

    return NULL;
}

