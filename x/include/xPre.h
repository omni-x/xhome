#ifndef _xPre_h__
#define _xPre_h__

#include <windows.h>
#include <assert.h>
#include <tchar.h>
#include <io.h>
#include <direct.h>
#include <string>
#include <deque>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>
#include <streambuf>
#include <iomanip>
#include <ios>


/////////////////////////// Delete Macro ///////////////////////////////////////

#define SAFE_DELETE(p)          { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p)    { if(p) { delete[] (p);   (p)=NULL; } }


#define __STRING__IMPL(x)   #x
#define __STRING__(x)   __STRING__IMPL(x)
#define __DEF_FILE_POS__() __FILE__ "(" __STRING__(__LINE__)"):"
#define __FILE_AND_LINE__(act,msg)  __DEF_FILE_POS__()"************:"act": "msg 
#define _TODO_(msg) message(__FILE_AND_LINE__("TODO", msg))
#define _FIX_(msg) message(__FILE_AND_LINE__("FIX", msg))
#define _XXX_(msg) message(__FILE_AND_LINE__("XXX", msg))

#pragma warning(disable: 4251)

#endif