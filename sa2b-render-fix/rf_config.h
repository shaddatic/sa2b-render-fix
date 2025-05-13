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
    const c8*   sect;
    const c8*   key;
    const int   def;
}
RFS_CNF_INT;

typedef struct
{
    const c8*   sect;
    const c8*   key;
    const bool  def;
}
RFS_CNF_BOOL;

typedef struct
{
    const c8*   sect;
    const c8*   key;
    const f32   def;
}
RFS_CNF_FLOAT;

typedef struct
{
    const c8*   sect;
    const c8*   key;
    const c8*   def;
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
int32_t   RF_ConfigGetInt(    const RFS_CNF_INT*    pCnf );
bool      RF_ConfigGetBool(   const RFS_CNF_BOOL*   pCnf );
f64       RF_ConfigGetFloat(  const RFS_CNF_FLOAT*  pCnf );
const c8* RF_ConfigGetString( const RFS_CNF_STRING* pCnf );

/** Config set **/
void        RF_ConfigSetInt(    const RFS_CNF_INT*    pCnf, int       set );
void        RF_ConfigSetBool(   const RFS_CNF_BOOL*   pCnf, bool      set );
void        RF_ConfigSetFloat(  const RFS_CNF_FLOAT*  pCnf, f64       set );
void        RF_ConfigSetString( const RFS_CNF_STRING* pCnf, const c8* set );

/****** Config Direct *******************************************************/
/** Config get **/
int32_t   RF_ConfigDirectGetInt(    const c8* section, const c8* key, int       def );
bool      RF_ConfigDirectGetBool(   const c8* section, const c8* key, bool      def );
f64       RF_ConfigDirectGetFloat(  const c8* section, const c8* key, f64       def );
const c8* RF_ConfigDirectGetString( const c8* section, const c8* key, const c8* def );

/** Config set **/
void        RF_ConfigDirectSetInt(    const c8* section, const c8* key, int       set );
void        RF_ConfigDirectSetBool(   const c8* section, const c8* key, bool      set );
void        RF_ConfigDirectSetFloat(  const c8* section, const c8* key, f64       set );
void        RF_ConfigDirectSetString( const c8* section, const c8* key, const c8* set );

EXTERN_END

#endif/*_RF_CONFIG_H_*/
