#ifndef _xlicensePre_h__
#define _xlicensePre_h__

#include "../../include/xPre.h"

#   if defined( XLICENSE_EXPORTS )
#       define _xlicense_ __declspec(dllexport)
#   else
#       define _xlicense_ __declspec(dllimport)
#   endif

#endif
