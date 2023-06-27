#pragma once

DataRef(task*, ALO_TVTaskPointer, 0x1AED288);

TaskFuncPtr(ALO_TVExecutor, 0x55C540);
TaskFuncPtr(ALO_TVDisplayer, 0x55C9E0);
TaskFuncPtr(ALO_TVDestructor, 0x55CB70);

FuncPtr(void, __cdecl, ALO_TVCreate, (NJS_POINT3* position), 0x55CB90);