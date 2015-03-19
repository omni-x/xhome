#ifndef _xMaterial_h__
#define _xMaterial_h__

#include "xPre.h"

struct xColorCard
{
    unsigned int    id_;
    unsigned int    rgb_;
    unsigned int    card_;
    std::string     name_;

    xColorCard() :  name_(""), 
        id_(0), 
        card_(0), 
        rgb_(0)
    {

    }
    xColorCard(unsigned int rgb, unsigned int card, const std::string& name, unsigned int id = 0)
        :   name_(name), 
        id_(id), 
        card_(card), 
        rgb_(rgb)
    {

    }
    const xColorCard& operator = (const xColorCard &src)
    {
        id_     = src.id_;
        rgb_    = src.rgb_;
        card_   = src.card_;
        name_   = src.name_;
        return *this;
    }
    xColorCard(const xColorCard& src)
    {
        this->operator = (src);
    }
    bool operator ==(const xColorCard &other) const
    {
        if ( (name_ == other.name_) && 
            (card_ == other.card_) && 
            (rgb_ == other.rgb_) )
            return true;
        return false;
    }
};
typedef xColorCard* lpxColorCard;
typedef std::vector<lpxColorCard> lpxColorCardArray;

struct xMaterial
{
    std::string     name_;
    xColorCard      color_;
    double          weight_;
};
typedef xMaterial* lpxMaterial;
typedef std::vector<lpxMaterial> lpxMaterialArray;

#endif
