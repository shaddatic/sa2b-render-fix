/*
*   SA2 Render Fix - '/rf_config.h'
*
*   Description:
*       Render Fix config reading, setting, & constants.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_CONFIG_H_
#define _RF_CONFIG_H_

/************************/
/*  Structure           */
/************************/
typedef struct
{
    const utf8* sect;
    const utf8* key;
    const int   def;
}
RFS_CNF_INT;

typedef struct
{
    const utf8* sect;
    const utf8* key;
    const bool  def;
}
RFS_CNF_BOOL;

typedef struct
{
    const utf8* sect;
    const utf8* key;
    const f32   def;
}
RFS_CNF_FLOAT;

typedef struct
{
    const utf8* sect;
    const utf8* key;
    const utf8* def;
}
RFS_CNF_STRING;

/************************/
/*  Includes            */
/************************/
/** Config definitions **/
#include <rf_config/rfcnf_def.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
/****** Init ****************************************************************/
void        RF_ConfigInit( void );  /* Open config file                     */
void        RF_ConfigEnd(  void );  /* Save & free config file              */

/****** Config ***************************************************************/
/** Config get **/
int32_t     RF_ConfigGetInt(    const RFS_CNF_INT*    pCnf );
bool        RF_ConfigGetBool(   const RFS_CNF_BOOL*   pCnf );
float64_t   RF_ConfigGetFloat(  const RFS_CNF_FLOAT*  pCnf );
const utf8* RF_ConfigGetString( const RFS_CNF_STRING* pCnf );

/** Config set **/
void        RF_ConfigSetInt(    const RFS_CNF_INT*    pCnf, int         set );
void        RF_ConfigSetBool(   const RFS_CNF_BOOL*   pCnf, bool        set );
void        RF_ConfigSetFloat(  const RFS_CNF_FLOAT*  pCnf, float64_t   set );
void        RF_ConfigSetString( const RFS_CNF_STRING* pCnf, const utf8* set );

/****** Config Direct *******************************************************/
/** Config get **/
int32_t     RF_ConfigDirectGetInt(    const utf8* section, const utf8* key, int         def );
bool        RF_ConfigDirectGetBool(   const utf8* section, const utf8* key, bool        def );
float64_t   RF_ConfigDirectGetFloat(  const utf8* section, const utf8* key, float64_t   def );
const utf8* RF_ConfigDirectGetString( const utf8* section, const utf8* key, const utf8* def );

/** Config set **/
void        RF_ConfigDirectSetInt(    const utf8* section, const utf8* key, int         set );
void        RF_ConfigDirectSetBool(   const utf8* section, const utf8* key, bool        set );
void        RF_ConfigDirectSetFloat(  const utf8* section, const utf8* key, float64_t   set );
void        RF_ConfigDirectSetString( const utf8* section, const utf8* key, const utf8* set );

EXTERN_END

#endif/*_RF_CONFIG_H_*/
