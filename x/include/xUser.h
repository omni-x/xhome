#ifndef _xUser_h__
#define _xUser_h__

#include "xPre.h"

struct xUser
{
    unsigned int id_;
    std::string name_;
    std::string pwd_;

    xUser() : name_(""), id_(0), pwd_("")
    {

    }
    const xUser& operator = (const xUser &src)
    {
        name_   = src.name_;
        id_     = src.id_;
        pwd_    = src.pwd_;
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
             (pwd_ == other.pwd_) )
            return true;
        return false;
    }
};
typedef xUser* lpxUser;
typedef std::vector<lpxUser> lpxUserArray;
typedef lpxUserArray* lpxUserArrayPtr;;

#endif