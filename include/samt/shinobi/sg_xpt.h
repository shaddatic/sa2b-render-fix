/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/shinobi/sg_xpt.h'
*
*   Definition:
*     Shinobi global system types.
*/
#ifndef H_SG_XPT
#define H_SG_XPT

EXTERN_START

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
