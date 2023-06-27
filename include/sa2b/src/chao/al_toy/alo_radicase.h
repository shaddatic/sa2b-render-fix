#pragma once

struct task;

DataRef(task*, ALO_RadicaseTaskPointer, 0x1AED2E0);

TaskFuncPtr(ALO_RadicaseExecutor, 0x57C840);
TaskFuncPtr(ALO_RadicaseDisplayer, 0x57CA80);
TaskFuncPtr(ALO_RadicaseDestructor, 0x57CC80);

FuncPtr(sint32, __cdecl, ALO_RadicaseCreate, (NJS_POINT3* pPos), 0x57CCA0);