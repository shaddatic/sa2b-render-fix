/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/shinobi/sg_xpt.h'
*
*   Definition:
*     Shinobi global system types.
*/
#ifndef H_SG_XPT
#define H_SG_XPT

EXTERN_START

/********************************/
/*  Types                       */
/********************************/
/****** Integer *********************************************************************************/
typedef u8                          Uint8;  /* unsigned 1 byte integer                          */
typedef i8                          Sint8;  /* signed 1 byte integer                            */
typedef u16                         Uint16; /* unsigned 2 byte integer                          */
typedef i16                         Sint16; /* signed 2 byte integer                            */
typedef u32                         Uint32; /* unsigned 4 byte integer                          */
typedef i32                         Sint32; /* signed 4 byte integer                            */

/****** Angles **********************************************************************************/
typedef Sint32                      Angle;  /* hardware angle                                   */
typedef Sint16                      Sangle; /* hardware angle, as 2 byte integer                */

/****** Default Integer *************************************************************************/
typedef Sint32                      Int;    /* default integer                                  */

/****** Real Number *****************************************************************************/
typedef float                       Float;  /* 4 byte real number                               */

/****** Void ************************************************************************************/
typedef void                        Void;   /* void type                                        */

/****** Boolean *********************************************************************************/
typedef Sint32                      Bool;   /* 4 byte boolean                                   */

EXTERN_END

#endif/*H_SG_XPT*/
