#include <windows.h>
#include "screen.h"

screen::screen() : xLen((double)GetSystemMetrics(SM_CXSCREEN)),
                                     yLen((double)GetSystemMetrics(SM_CYSCREEN)){}
double screen::getXLen(void){return xLen;}
double screen::getYLen(void){return yLen;}
