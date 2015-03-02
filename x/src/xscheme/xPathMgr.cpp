#include "xPathMgr.h"

XPathMgr::XPathMgr() : dbFilePath_("")
{
    init();
}

XPathMgr::~XPathMgr()
{
    uninit();
}

XPathMgr& XPathMgr::instance()
{
    static XPathMgr s_pathmgr;
    return s_pathmgr;
}

HMODULE WINAPI ModuleFromAddress() 
{ 
    MEMORY_BASIC_INFORMATION mbi; 
    if(::VirtualQuery(ModuleFromAddress, &mbi, sizeof(mbi)) != 0) 
    { 
        return (HMODULE)mbi.AllocationBase; 
    } 
    else 
    { 
        return NULL; 
    } 
}

void XPathMgr::init()
{
    char szFull[_MAX_PATH]      = {0};
    char szDrive[_MAX_DRIVE]    = {0};
    char szDir[_MAX_DIR]        = {0};
    char szFileName[_MAX_FNAME] = {0};
    char szExt[_MAX_EXT]        = {0};

    ::GetModuleFileName( ModuleFromAddress(), szFull, sizeof(szFull)/sizeof(char) );
    _tsplitpath_s( szFull, szDrive, _MAX_DRIVE, szDir, _MAX_DIR, szFileName, _MAX_FNAME, szExt, _MAX_EXT );
    _tcscpy_s( szFull, _MAX_PATH, szDrive );
    _tcscat_s( szFull, szDir );

    std::string strFullPath(szFull);

    dbFilePath_ = strFullPath + "scheme\\";

    makeDir(dbFilePath_);
}

void XPathMgr::uninit()
{

}

bool XPathMgr::makeDir(const std::string & dir)
{
    std::string c_dir = dir;
    const char *path = c_dir.c_str();
    char *tmp = (char*)path;
    while (*tmp)  
    {  
        if (*tmp == '\\')  
        {  
            *tmp = '\0';  
            if (_taccess(path, 0))
            {  
                _tmkdir(path);
            }  
            *tmp = '\\';  
        }  
        ++tmp;  
    }
    if ( _taccess( c_dir.c_str(), 0 ) != -1 )
        return true;

    return false;
}
