#pragma once

#include <sa2b/src/figure/knuckles.h>

DataRef(NJS_MATRIX, mtx_RougeBootL, 0x01A51BBC);
DataRef(NJS_MATRIX, mtx_RougeBootR, 0x01A51C1C);

FuncPtr(void, __cdecl, RougeMotionCallBack, (NJS_CNK_OBJECT*), 0x007304D0);