#ifndef _xstorePre_h__
#define _xstorePre_h__

#include "../../include/xPre.h"

#   if defined( XSTORE_EXPORTS )
#       define _xstore_ __declspec(dllexport)
#   else
#       define _xstore_ __declspec(dllimport)
#   endif

#endif
