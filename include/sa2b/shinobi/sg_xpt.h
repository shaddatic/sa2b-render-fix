/*
*   Sonic Adventure Mod Tools (SA2B) - '/shinobi/sg_xpt.h'
*
*   Contains Shinobi global defines and types
*
*   Contributors:
*   -   SEGA,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/

#ifndef _SG_XPT_H_
#define _SG_XPT_H_

/****** GLOBAL DECLARATION **********************************************/
typedef uint8           Uint8;          /*  unsigned 1 byte integer     */

typedef sint8           Sint8;          /*  signed 1 byte integer       */

typedef uint16          Uint16;         /*  unsigned 2 byte integer     */

typedef sint16          Sint16;         /*  signed 2 byte integer       */

typedef uint32          Uint32;         /*  unsigned 4 byte integer     */

typedef sint32          Sint32;         /*  signed 4 byte integer       */

typedef sint32          Int;            /*  default integer             */

typedef float32         Float;          /*  4 byte real number          */

typedef void            Void;           /*  void                        */

typedef bool32          Bool;           /*  Bool                        */

/****** GLOBAL CONSTANT *************************************************/
#ifndef FALSE
#define FALSE           (0)
#endif
#ifndef TRUE
#define TRUE            (1)
#endif

#ifndef ON
#define ON              (1)
#endif
#ifndef OFF
#define OFF             (0)
#endif

/****** GLOBAL MACRO ****************************************************/
#ifndef MAX
#define MAX(x, y)       ((x) > (y) ? (x) : (y))             /* maximum  */
#endif
#ifndef MIN
#define MIN(x, y)       ((x) < (y) ? (x) : (y))             /* minimum  */
#endif
#ifndef ABS
#define ABS(x)          ((x) < 0 ? -(x) : (x))              /* absolute */
#endif


#endif
/****** End of file *****************************************************/
