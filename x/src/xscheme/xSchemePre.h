#ifndef _xSchemePre_h__
#define _xSchemePre_h__

#include "../../include/xPre.h"

#   if defined( XSCHEME_EXPORTS )
#       define _xscheme_ __declspec(dllexport)
#   else
#       define _xscheme_ __declspec(dllimport)
#   endif

#endif
