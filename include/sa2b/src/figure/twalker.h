#pragma once

#include <sa2b/src/figure/ewalker.h>

DataRef(NJS_MATRIX, mtx_TornadoBazooka, 0x01A52030);
DataRef(NJS_MATRIX, mtx_TornadoBoosterL, 0x01A51EDC);
DataRef(NJS_MATRIX, mtx_TornadoBoosterR, 0x01A51E4C);

FuncPtr(void, __cdecl, TornadoMotionCallBack, (NJS_CNK_OBJECT*), 0x00747940);