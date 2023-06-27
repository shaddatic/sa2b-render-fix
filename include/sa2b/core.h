/*
*	Sonic Adventure Mod Tools - Core Header
*/

#ifndef _SAMT_CORE_
#define _SAMT_CORE_

#pragma comment(lib, "sa2b-mod-toolkit.lib")

#ifdef _WIN64
static_assert(false, "You cannot use x64 to build a mod for SA2 or SADX");
#endif

#ifndef __cplusplus
static_assert(false, "C++20 is required for this mod toolkit");
#endif

/*
*	Integer types
*/
typedef unsigned __int8		uint8;		/*  unsigned 1 byte integer	*/
typedef signed	 __int8		sint8;		/*  signed 1 byte integer	*/
typedef unsigned __int16	uint16;		/*  unsigned 2 byte integer	*/
typedef signed	 __int16	sint16;		/*  signed 2 byte integer	*/
typedef unsigned __int32	uint32;		/*  unsigned 4 byte integer	*/
typedef signed	 __int32	sint32;		/*  signed 4 byte integer	*/
typedef unsigned __int64	uint64;		/*  unsigned 8 byte integer	*/
typedef signed	 __int64	sint64;		/*  signed 8 byte integer	*/

typedef signed	   int		sint;
typedef unsigned   int		uint;

/*
*	Floating Point types
*/
typedef float				float32;	/*  4 byte real number		*/
typedef double				float64;	/*  8 byte real number		*/

/*
*	String and Character types & defines
*/
typedef char				ansi;		/*  ANSI character (none)			*/
typedef char				utf8;		/*  UTF-8 character (u8)			*/

/*
*	Other
*/
typedef sint32				bool32;		/*  4 byte boolean          */

/*
*	Game Data References
*/
#define DataRef(TYPE, NAME, ADDR)	  inline TYPE&	     NAME = *(TYPE*)ADDR
#define DataPtr(TYPE, NAME, ADDR)	  inline TYPE* const NAME =  (TYPE*)ADDR
#define DataAry(TYPE, NAME, ADDR, NB) typedef TYPE NAME##_t NB; DataRef(NAME##_t, NAME, ADDR)

/*
*	Game Function References
*/
#define FuncPtr(TYPE, METH, NAME, ARGS, ADDR) inline TYPE (METH *const NAME)ARGS = (TYPE (METH *const)ARGS)ADDR

/*
*	Game Task Function References
*/
#define TaskFuncPtr(NAME, ADDR) FuncPtr(void, __cdecl, NAME, (TASK* tp), ADDR)

/*
*	Core Functions
*/
void		SAMT_Init(const char* pOptPath, const void* pOptHelperFunctions);

const char*	GetModPath();

#endif /* _SAMT_CORE_ */