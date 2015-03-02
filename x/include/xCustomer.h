#ifndef _xCustomer_h__
#define _xCustomer_h__

#include "xPre.h"

struct xCustomer
{
    std::string name_;
    unsigned int id_;
    std::string Tel_;
    std::string QQ_;

    xCustomer() : name_(""), id_(0), Tel_(""), QQ_("")
    {

    }
    const xCustomer& operator = (const xCustomer &src)
    {
        name_   = src.name_;
        id_     = src.id_;
        Tel_    = src.Tel_;
        QQ_     = src.QQ_;
        return *this;
    }
    xCustomer(const xCustomer& src)
    {
        this->operator = (src);
    }
    bool operator ==(const xCustomer &other) const
    {
        if ( (name_ == other.name_) && 
             (id_ == other.id_) && 
             (Tel_ == other.Tel_) && 
             (QQ_ == other.QQ_) )
            return true;
        return false;
    }
};
typedef xCustomer* lpxCustomer;
typedef std::vector<lpxCustomer> lpxCustomerArray;

#endif