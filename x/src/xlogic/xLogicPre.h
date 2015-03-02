#ifndef _xlogicPre_h__
#define _xlogicPre_h__

#include "../../include/xPre.h"

#   if defined( XLOGIC_EXPORTS )
#       define _xlogic_ __declspec(dllexport)
#   else
#       define _xlogic_ __declspec(dllimport)
#   endif

#endif
