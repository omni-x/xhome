#ifndef _xMaterials_h__
#define _xMaterials_h__

#include "xPre.h"

struct xMaterials
{
    std::string name_;
    unsigned int id_;

    xMaterials() : name_(""), id_(0)
    {

    }
    const xMaterials& operator = (const xMaterials &src)
    {
        name_   = src.name_;
        id_     = src.id_;
        return *this;
    }
    xMaterials(const xMaterials& src)
    {
        this->operator = (src);
    }
    bool operator ==(const xMaterials &other) const
    {
        if ( (name_ == other.name_) && 
             (id_ == other.id_) )
            return true;
        return false;
    }
};
typedef xMaterials* lpxMaterials;
typedef std::vector<lpxMaterials> lpxMaterialsArray;

#endif
