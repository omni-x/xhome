#ifndef _xOrder_h__
#define _xOrder_h__

#include "xPre.h"

struct xBuild
{
    unsigned int            id_;
    std::string             name_;

    xBuild() :  id_(0), 
                name_("")
    {

    }
    const xBuild& operator = (const xBuild &src)
    {
        id_     = src.id_;
        name_   = src.name_;
        return *this;
    }
    xBuild(const xBuild& src)
    {
        this->operator = (src);
    }
    bool operator ==(const xBuild &other) const
    {
        if ( (id_ == other.id_) && 
            (name_ == other.name_) )
            return true;
        return false;
    }
};
typedef xBuild* lpxBuild;
typedef std::vector<lpxBuild> lpxBuildArray;

struct xPlace
{
    unsigned int            id_;
    std::string             name_;

    xPlace() :  id_(0), 
                name_("")
    {

    }
    const xPlace& operator = (const xPlace &src)
    {
        id_         = src.id_;
        name_       = src.name_;
        return *this;
    }
    xPlace(const xPlace& src)
    {
        this->operator = (src);
    }
    bool operator ==(const xPlace &other) const
    {
        if ( (id_ == other.id_) && 
            (name_ == other.name_) ) 
            return true;
        return false;
    }
};
typedef xPlace* lpxPlace;
typedef std::vector<lpxPlace> lpxPlaceArray;

struct xOrder
{
    std::string     salesPerson_;   // 销售
    std::string     referrals_;     // 介绍人
    std::string     builder_;       // 施工
    double          area_;          // 建筑面积
    unsigned int    designer_;      // 设计师id
    lpxPlaceArray   arrPlace_;

    xOrder() :  salesPerson_(""), 
                referrals_(0), 
                builder_(""), 
                area_(0), 
                designer_(0)
    {

    }
    const xOrder& operator = (const xOrder &src)
    {
        salesPerson_    = src.salesPerson_;
        referrals_      = src.referrals_;
        builder_        = src.builder_;
        arrPlace_       = src.arrPlace_;
        designer_       = src.designer_;
        return *this;
    }
    xOrder(const xOrder& src)
    {
        this->operator = (src);
    }
    bool operator ==(const xOrder &other) const
    {
        if ( (salesPerson_ == other.salesPerson_) && 
            (referrals_ == other.referrals_) && 
            (builder_ == other.builder_) && 
            (designer_ == other.designer_) )
            return true;
        return false;
    }
};
typedef xOrder* lpxOrder;
typedef std::vector<lpxOrder> lpxOrderArray;

#endif
