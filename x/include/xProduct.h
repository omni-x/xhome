#ifndef _xProduct_h__
#define _xProduct_h__

#include "xPre.h"

struct xProduct
{
    std::string name_;
    unsigned int id_;

    xProduct() : name_(""), id_(0)
    {

    }
    const xProduct& operator = (const xProduct &src)
    {
        name_   = src.name_;
        id_     = src.id_;
        return *this;
    }
    xProduct(const xProduct& src)
    {
        this->operator = (src);
    }
    bool operator ==(const xProduct &other) const
    {
        if ( (name_ == other.name_) && 
             (id_ == other.id_) )
            return true;
        return false;
    }
};
typedef xProduct* lpxProduct;
typedef std::vector<lpxProduct> lpxProductArray;

#endif
