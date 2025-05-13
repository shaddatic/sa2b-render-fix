/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/writeop.h'
*
*   Description:
*     For writing CPU instructions and opcodes to the game's memory.
*/
#ifndef H_SAMT_WRITEOP
#define H_SAMT_WRITEOP

EXTERN_START

/********************************/
/*  Prototypes                  */
/********************************/
/****** Write Opcode ****************************************************************************/
/*
*   Description:
*     Write a long (32bit) jump instruction to the absolute address 'pTgt'.
*
*   Notes:
*     - Internally calls 'MemCopyProtected()'.
*
*   Parameters:
*     - pDst        : address to write the jump instruction to
*     - pTgt        : target of the jump instruction
*/
void    mtOpWriteJump( void* pDst, const void* pTgt );
/*
*   Description:
*     Write a call instruction to the absolute address 'pTgt'.
*
*   Notes:
*     - Internally calls 'MemCopyProtected()'.
*
*   Parameters:
*     - pDst        : address to write the call instruction to
*     - pTgt        : target of the call instruction
*/
void    mtOpWriteCall( void* pDst, const void* pTgt );
/*
*   Description:
*     Write a short (8bit) jump instruction to the absolute address 'pTgt'.
*
*   Notes:
*     - Internally calls 'MemCopyProtected()'.
*
*   Parameters:
*     - pDst        : address to write the jump instruction to
*     - pTgt        : target of the jump instruction
*/
void    mtOpWriteShortJump( void* pDst, const void* pTgt );
/*
*   Description:
*     Write a near return instruction with optional stack pop operand.
*
*   Notes:
*     - If 'nbPop' is '0', the regular '0xC3' variant of RETN will be used.
*
*   Parameters:
*     - pDst        : address to write the retn instruction to
*     - nbPop       : number of bytes to pop from the stack
*/
void    mtOpWriteRetn( void* pDst, s16 nbPop );
/*
*   Description:
*     Write a NOP instruction recursively.
*
*   Parameters:
*     - pDst        : address to write the retn instruction to
*     - nb          : number of NOP instructions to write
*/
void    mtOpWriteNop( void* pDst, size_t nb );
/*
*   Description:
*     Write a two-byte NOP instruction recursively.
*
*   Parameters:
*     - pDst        : address to write the retn instruction to
*     - nb          : number of two-byte NOP instructions to write
*/
void    mtOpWriteShortNop( void* pDst, size_t nb );

/********************************/
/*  Function Macros             */
/********************************/
/****** Write Opcode ****************************************************************************/
/*
*   Description:
*     Write a long jump (32bit) instruction to the absolute address 'tgt'.
*
*   Parameters:
*     - addr        : address to write the jump instruction to
*     - tgt         : target of the jump instruction
*/
#define WriteJump(addr, tgt)                mtOpWriteJump((void*)(addr), (void*)(tgt))
/*
*   Description:
*     Write a call instruction to the absolute address 'tgt'.
*
*   Parameters:
*     - addr        : address to write the call instruction to
*     - tgt         : target of the call instruction
*/
#define WriteCall(addr, tgt)                mtOpWriteCall((void*)(addr), (void*)(tgt))
/*
*   Description:
*     Write a short (8bit) jump instruction to the absolute address 'tgt'.
*
*   Parameters:
*     - addr        : address to write the jump instruction to
*     - tgt         : target of the jump instruction
*/
#define WriteShortJump(addr, tgt)           mtOpWriteShortJump((void*)(addr), (void*)(tgt))
/*
*   Description:
*     Write a block of NOP instructions using a start and end pointer.
*
*   Parameters:
*     - from        : starting address of the NOP block
*     - to          : end address of the NOP block (non-inclusive)
*/
#define WriteNOP(from, to)                  mtOpWriteNop((void*)(from), (((uintptr_t)to)-((uintptr_t)from)));
/*
*   Description:
*     Write a block of two-byte NOP instructions using a start and end pointer.
*
*   Notes:
*     - If the block size isn't a multiple of 2, a single byte will be missed at the end
*
*   Parameters:
*     - from        : starting address of the NOP block
*     - to          : end address of the NOP block (non-inclusive)
*/
#define WriteShortNOP(from, to)             mtOpWriteShortNop((void*)(from), (((uintptr_t)to)-((uintptr_t)from)) / 2);
/*
*   Description:
*     Write a return instruction to 'addr' with no additional opcodes.
*
*   Parameters:
*     - addr        : address to write RETN to
*/
#define WriteRetn(addr)                     mtOpWriteRetn((void*)(addr), 0)
/*
*   Description:
*     Write a return instruction to 'addr' with an additional stack pop opcode.
*
*   Parameters:
*     - addr        : address to write RETN to
*/
#define WriteRetnPop(addr, nb)              mtOpWriteRetn((void*)(addr), (nb))

/****** Other ***********************************************************************************/
/*
*   Description:
*     Replace CALL instruction with NOPs. Should only be used on CALLs where the
*   caller cleans the stack.
*
*   Parameters:
*     - addr    : address of the CALL instruction to kill
*/
#define KillCall(addr)                      mtOpWriteNop((void*)(addr), 5);

EXTERN_END

#endif/*H_SAMT_WRITEOP*/
