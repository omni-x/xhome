#ifndef _xsqlPre_h__
#define _xsqlPre_h__

#include "../../include/xPre.h"

#   if defined( XSQL_EXPORTS )
#       define _xsql_ __declspec(dllexport)
#   else
#       define _xsql_ __declspec(dllimport)
#   endif

#endif
