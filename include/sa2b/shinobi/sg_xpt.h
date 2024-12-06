/*
*   Sonic Adventure Mod Tools (SA2B) - '/shinobi/sg_xpt.h'
*
*   Definition:
*     Shinobi global system types.
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SG_XPT
#define H_SG_XPT

#undef TRUE                     /* windows headers may define these                 */
#undef FALSE                    /* ^^^                                              */

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Boolean *********************************************************************/
#define TRUE                    (1) /* boolean 'true'                               */
#define FALSE                   (0) /* boolean 'false'                              */

/****** Switch **********************************************************************/
#define ON                      (1) /* switch 'on'                                  */
#define OFF                     (0) /* switch 'off'                                 */

/************************/
/*  Typedefs            */
/************************/
/****** Integer *********************************************************************/
typedef unsigned __int8         Uint8;  /* unsigned 1 byte integer                  */
typedef signed   __int8         Sint8;  /* signed 1 byte integer                    */
typedef unsigned __int16        Uint16; /* unsigned 2 byte integer                  */
typedef signed   __int16        Sint16; /* signed 2 byte integer                    */
typedef unsigned __int32        Uint32; /* unsigned 4 byte integer                  */
typedef signed   __int32        Sint32; /* signed 4 byte integer                    */

/****** Default Integer *************************************************************/
typedef signed __int32          Int;    /* default integer                          */

/****** Real Number *****************************************************************/
typedef float                   Float;  /* 4 byte real number                       */

/****** Void ************************************************************************/
typedef void                    Void;   /* void type                                */

/****** Boolean *********************************************************************/
typedef signed __int32          Bool;   /* 4 byte boolean                           */

EXTERN_END

#endif/*H_SG_XPT*/
