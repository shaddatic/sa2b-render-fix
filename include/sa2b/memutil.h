/*
*   Sonic Adventure Mod Tools (SA2B) - '/memutil.h'
*
*   Contains functions to modify or read executable data
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_MEMUTIL_H_
#define _SAMT_MEMUTIL_H_

/************************/
/*  External Functions  */
/************************/
EXTERN void* MemSet(void* p, uint8_t val, size_t size);

/************************/
/*  Constants           */
/************************/
/** Address thresholds **/
#define STACK_THRESHOLD     ((void*)0x00400000)
#define WPROT_THRESHOLD     ((void*)0x0087342C)

/** Memory page permissions **/
#define PERM_NONE           (0x01) /* No permissions            */
#define PERM_READ           (0x02) /* Read-only                 */
#define PERM_WRITE          (0x08) /* write-copy (read-copy)    */
#define PERM_EXEC           (0x10) /* Execute                   */

#define PERM_READ_WRITE     (0x04) /* Read & write              */
#define PERM_EXEC_READ      (0x20) /* Execute & read-only       */
#define PERM_EXEC_WRITE     (0x80) /* Execute & write-copy      */

#define PERM_ALL            (0x40) /* Execute, read, & write    */

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Set page protection permissions, 
    returns true on success **/
bool    MemProtectSet(void* p, size_t nbByte, uint32_t perms);

/** Copy/Move to protected memory in 'WPROT' range, leaves 
    memory page with all permissions (EXEC, READ, & WRITE) **/
void    MemCopyProtected( void* pDst, const void* pSrc, size_t nb );
void    MemMoveProtected( void* pDst, const void* pSrc, size_t nb );

/** Write Call/Jump instructions, 
    internally calls 'MemCopyProtected()' **/
void    MemWriteJump( void* pDst, const void* pJump );
void    MemWriteCall( void* pDst, const void* pCall );

/** Endianness **/
void    SwapEndianness64( void* p );
void    SwapEndianness32( void* p );
void    SwapEndianness16( void* p );

EXTERN_END

/************************/
/*  Function Macros     */
/************************/
/** Copy data to protected memory **/
#define WriteMemory(waddr, daddr, size)     MemCopyProtected((void*)(waddr), (void*)(daddr), (size_t)(size))

/** Write lvalue data to protected memory **/
#define WriteData(addr, data, type)       { type _v_ = (type)(data); WriteMemory((addr), &_v_, sizeof(type));            }
#define WritePointer(addr, ptr)             WriteData((addr), (ptr), void*)

/** Write string of lvalue **/
#define WriteMulti(waddr, val, nb)        { uint8_t _a_[nb]; MemSet(_a_, val, nb); WriteMemory((void*)(waddr), _a_, (nb)); }

/** NOP call instruction **/
#define KillCall(waddr)                     WriteMulti((waddr), 0x90, 0x05);

/** Write OP instructions **/
#define WriteJump(waddr, jaddr)             MemWriteJump((void*)(waddr), (void*)(jaddr))
#define WriteCall(waddr, caddr)             MemWriteCall((void*)(waddr), (void*)(caddr))
#define WriteNoOP(from, to)                 WriteMulti((from), 0x90, ((to) - (from)));
#define WriteRetn(addr)                     WriteData((addr), 0xC3, uint8_t)

/** Copy array to protected memory **/
#define WriteArray(waddr, ary)              WriteMemory((void*)(waddr), (void*)(ary), sizeof((ary)))

/** Check for Stack Pointer **/
#define IsStack(p)                          (((void*)(p)) < STACK_THRESHOLD)

/** Check for Protected Pointer **/
#define IsProtected(p)                      (((void*)(p)) < WPROT_THRESHOLD)

/** Endiness Macro **/
#define SwapEndianness(ptr)                 if (sizeof(*ptr) == 8) { SwapEndianness64(ptr); } else \
                                            if (sizeof(*ptr) == 4) { SwapEndianness32(ptr); } else \
                                            if (sizeof(*ptr) == 2) { SwapEndianness16(ptr); }

#endif /* _SAMT_MEMUTIL_H_ */
