/*
*   Sonic Adventure Mod Tools (SA2B) - '/memtools.h'
*
*   Contains functions to modify or read executable data
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_MEMTOOLS_H_
#define _SAMT_MEMTOOLS_H_

/************************/
/*  External Functions  */
/************************/
EXTERN void* MemSet(void* p, int val, size_t size);

/************************/
/*  Constants           */
/************************/
#define STACK_THRESHOLD     ((void*)0x00400000)
#define CONST_THRESHOLD     ((void*)0x0087342C)

/************************/
/*  Functions           */
/************************/
EXTERN_START

void    WriteProtectedMemory(void* writeaddr, const void* dataaddr, size_t elemsize);

void    WriteInstructionJump(void* writeaddr, const void* jumpaddr);
void    WriteInstructionCall(void* writeaddr, const void* calladdr);

void    SwapEndianness64(void* p);
void    SwapEndianness32(void* p);
void    SwapEndianness16(void* p);

EXTERN_END

/************************/
/*  Function Macros     */
/************************/
#define WriteMemory(waddr, daddr, size)     WriteProtectedMemory((void*)(waddr), (void*)(daddr), (size_t)(size))

#define WriteData(addr, data, type)       { type _v_ = (type)(data); WriteMemory((addr), &_v_, sizeof(type));            }
#define WritePointer(addr, ptr)             WriteData((addr), (ptr), void*)

#define WriteMulti(waddr, val, nb)        { uint8 _a_[nb]; MemSet(_a_, val, nb); WriteMemory((void*)(waddr), _a_, (nb)); }

#define WriteNoOP(from, to)                 WriteMulti((from), 0x90, ((to) - (from)));
#define KillCall(waddr)                     WriteMulti((waddr), 0x90, 0x05);

#define WriteJump(waddr, jaddr)             WriteInstructionJump((void*)(waddr), (void*)(jaddr))
#define WriteCall(waddr, caddr)             WriteInstructionCall((void*)(waddr), (void*)(caddr))
#define WriteRetn(addr)                     WriteData((addr), 0xC3, uint8)

#define WriteArray(waddr, ary)              WriteMemory((void*)(waddr), (void*)(ary), sizeof((ary)))

/** Check for Stack Pointer **/
#define IsOnStack(p)                        (((void*)(p)) < STACK_THRESHOLD)

/** Endiness Macro **/
#define SwapEndianness(ptr)                 if (sizeof(*ptr) == 8) { SwapEndianness64(ptr); } else \
                                            if (sizeof(*ptr) == 4) { SwapEndianness32(ptr); } else \
                                            if (sizeof(*ptr) == 2) { SwapEndianness16(ptr); }

#endif /* _SAMT_MEMTOOLS_H_ */
