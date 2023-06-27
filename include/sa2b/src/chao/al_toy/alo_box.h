#pragma once

#include <sa2b/src/task.h>

struct task;

DataRef(task*, ALO_BoxTaskPointer, 0x1AED32C);

TaskFuncPtr(ALO_BoxExecutor, 0x5801C0);
TaskFuncPtr(ALO_BoxDisplayer, 0x580510);
TaskFuncPtr(ALO_BoxDestructor, 0x580870);

FuncPtr(void, __cdecl, ALO_BoxCreate, (NJS_POINT3* pPos), 0x580890);