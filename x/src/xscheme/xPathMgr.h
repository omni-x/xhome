#ifndef _xPathMgr_h__
#define _xPathMgr_h__

#include "../../include/xError.h"
#include "xSchemePre.h"

class _xscheme_ XPathMgr
{
public:
    ~XPathMgr();
    static XPathMgr& instance();

protected:
    XPathMgr();

public:
    std::string getDBPath();
    bool makeDir(const std::string & dir);

protected:
    void init();
    void uninit();

private:
    std::string dbFilePath_;
};

inline std::string XPathMgr::getDBPath()
{
    return dbFilePath_;
}

#endif
