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
    unsigned int    id_;
    std::string     name_;
    unsigned int    color_;
    double          weight_;

    xMaterial() : name_(""), id_(0), color_(0), weight_(0)
    {

    }
    xMaterial(const std::string& name, unsigned int color, double weight)
        : id_(0), name_(name), color_(color), weight_(weight)
    {

    }
    xMaterial(unsigned int id, const std::string& name, unsigned int color, double weight)
        : id_(id), name_(name), color_(color), weight_(weight)
    {

    }
    const xMaterial& operator = (const xMaterial &src)
    {
        name_   = src.name_;
        id_     = src.id_;
        color_  = src.color_;
        weight_ = src.weight_;
        return *this;
    }
    xMaterial(const xMaterial& src)
    {
        this->operator = (src);
    }
    bool operator ==(const xMaterial &other) const
    {
        if ( (name_ == other.name_) && 
            (id_ == other.id_) && 
            (color_ == other.color_) && 
            (weight_ == other.weight_) )
            return true;
        return false;
    }
};
typedef xMaterial* lpxMaterial;
typedef std::vector<lpxMaterial> lpxMaterialArray;


struct xUseOfMaterial
{
    unsigned int    id_;
    unsigned int    material_;
    double          weight_;

    xUseOfMaterial() : id_(0), material_(0), weight_(0)
    {

    }
    xUseOfMaterial(unsigned int material, double weight)
        : id_(0), material_(material), weight_(weight)
    {

    }
    xUseOfMaterial(unsigned int id, unsigned int material, double weight)
        : id_(id), material_(material), weight_(weight)
    {

    }
    const xUseOfMaterial& operator = (const xUseOfMaterial &src)
    {
        id_         = src.id_;
        material_   = src.material_;
        weight_     = src.weight_;
        return *this;
    }
    xUseOfMaterial(const xUseOfMaterial& src)
    {
        this->operator = (src);
    }
    bool operator ==(const xUseOfMaterial &other) const
    {
        if ( (id_ == other.id_) && 
             (material_ == other.material_) && 
             (weight_ == other.weight_) )
            return true;
        return false;
    }
};
typedef xUseOfMaterial* lpxUseOfMaterial;
typedef std::vector<lpxUseOfMaterial> lpxUseOfMaterialArray;


#endif
