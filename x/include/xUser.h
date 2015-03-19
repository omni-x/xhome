#ifndef _xUser_h__
#define _xUser_h__

#include "xPre.h"


enum emUserType
{
    kAdmin = 0, 
    kSaleman = 1, 
};

struct xUser
{
    unsigned int    id_;
    std::string     name_;
    std::string     pwd_;
    emUserType      type_;

    xUser() : name_(""), id_(0), pwd_(""), type_(kSaleman)
    {

    }
    xUser(const std::string& name, const std::string& pwd, emUserType etype)
        : id_(0), name_(name), pwd_(pwd), type_(etype)
    {

    }
    xUser(unsigned int id, const std::string& name, const std::string& pwd, emUserType etype)
        : id_(id), name_(name), pwd_(pwd), type_(etype)
    {

    }
    const xUser& operator = (const xUser &src)
    {
        name_   = src.name_;
        id_     = src.id_;
        pwd_    = src.pwd_;
        type_   = src.type_;
        return *this;
    }
    xUser(const xUser& src)
    {
        this->operator = (src);
    }
    bool operator ==(const xUser &other) const
    {
        if ( (name_ == other.name_) && 
             (id_ == other.id_) && 
             (pwd_ == other.pwd_) && 
             (type_ == other.type_) )
            return true;
        return false;
    }
};
typedef xUser* lpxUser;
typedef std::vector<lpxUser> lpxUserArray;
typedef lpxUserArray* lpxUserArrayPtr;;

#endif