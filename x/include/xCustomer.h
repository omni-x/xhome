#ifndef _xCustomer_h__
#define _xCustomer_h__

#include "xPre.h"

struct xCustomerGroup
{
    unsigned int    id_;
    std::string     text_;

    const xCustomerGroup& operator = (const xCustomerGroup &src)
    {
        id_     = src.id_;
        text_   = src.text_;        
        return *this;
    }
    xCustomerGroup(const xCustomerGroup& src)
    {
        this->operator = (src);
    }
    bool operator ==(const xCustomerGroup &other) const
    {
        if ( (id_ == other.id_) && 
            (text_ == other.text_) )
            return true;
        return false;
    }
};
typedef xCustomerGroup* lpxCustomerGroup;
typedef std::vector<lpxCustomerGroup> lpxCustomerGroupArray;

struct xCustomer
{
    std::string     name_;
    unsigned int    id_;
    std::string     Tel_;
    std::string     QQ_;
    unsigned int    group_;

    xCustomer() :   name_(""), 
                    id_(0), 
                    Tel_(""), 
                    QQ_(""), 
                    group_(0)
    {

    }
    const xCustomer& operator = (const xCustomer &src)
    {
        name_           = src.name_;
        id_             = src.id_;
        Tel_            = src.Tel_;
        QQ_             = src.QQ_;
        group_          = src.group_;
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
             (QQ_ == other.QQ_) && 
             (group_ == other.group_))
            return true;
        return false;
    }
};
typedef xCustomer* lpxCustomer;
typedef std::vector<lpxCustomer> lpxCustomerArray;


struct xDesigner
{
    unsigned int    id_;
    std::string     name_;
    std::string     Tel_;
    std::string     QQ_;
    unsigned int    rebate_;    // ·µµã
};
typedef xDesigner* lpxDesigner;
typedef std::vector<lpxDesigner> lpxDesignerArray;


#endif
