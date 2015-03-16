#ifndef _xCustomer_h__
#define _xCustomer_h__

#include "xPre.h"

struct xCustomer
{
    std::string     name_;
    unsigned int    id_;
    std::string     Tel_;
    std::string     QQ_;

    xCustomer() :   name_(""), 
                    id_(0), 
                    Tel_(""), 
                    QQ_("")
    {

    }
    const xCustomer& operator = (const xCustomer &src)
    {
        name_           = src.name_;
        id_             = src.id_;
        Tel_            = src.Tel_;
        QQ_             = src.QQ_;
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


struct xBuild
{
    std::string             name_;
    std::vector<xBuild*>    arrBuild_;
};
typedef xBuild* lpxBuild;
typedef std::vector<lpxBuild> lpxBuildArray;

struct xPlace
{
    std::string     salesPerson_;   // 销售
    std::string     referrals_;     // 介绍人
    std::string     builder_;       // 施工
    double          buildingArea_;  // 建筑面积

    lpxBuildArray   arrBuild;

    xPlace() :  salesPerson_(""), 
                referrals_(0), 
                builder_("")
    {

    }
    const xPlace& operator = (const xPlace &src)
    {
        salesPerson_    = src.salesPerson_;
        referrals_      = src.referrals_;
        builder_        = src.builder_;
        return *this;
    }
    xPlace(const xPlace& src)
    {
        this->operator = (src);
    }
    bool operator ==(const xPlace &other) const
    {
        if ( (salesPerson_ == other.salesPerson_) && 
            (referrals_ == other.referrals_) && 
            (builder_ == other.builder_) )
            return true;
        return false;
    }
};
typedef xPlace* lpxPlace;
typedef std::vector<lpxPlace> lpxPlaceArray;

#endif
