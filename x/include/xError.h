#ifndef _xError_h__
#define _xError_h__

enum
{
    x_NoErr            = 0,
    x_Failure          = 1,
    x_Unimplemented    = 2,
    x_OutOfState       = 3,
    x_WrongVersion     = 4,
    x_BadIndex         = 5,
    x_ValueNotFound    = 6,
    x_BadArgument      = 7,
    x_ReadOnly         = 8,
    x_NotEnoughSpace   = 9,
    x_FileNotFound     = 10,
    x_NoMoreData       = 11,
};

typedef int xError;

#endif