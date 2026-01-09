/*
*   Common Utils - '/cnf.h'
*
*   Description:
*     Core config reading module and config definitions.
*/
#ifndef H_CMN_CONFIG
#define H_CMN_CONFIG

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Config Int Entry ************************************************************************/
typedef struct
{
    const c8*   sect;               /* config entry section                                     */
    const c8*   key;                /* config entry key                                         */
    const i32   def;                /* config entry default value                               */
}
CONFIG_INT;

/****** Config Bool Entry ***********************************************************************/
typedef struct
{
    const c8*   sect;               /* config entry section                                     */
    const c8*   key;                /* config entry key                                         */
    const bool  def;                /* config entry default value                               */
}
CONFIG_BOOL;

/****** Config Float Entry **********************************************************************/
typedef struct
{
    const c8*   sect;               /* config entry section                                     */
    const c8*   key;                /* config entry key                                         */
    const f32   def;                /* config entry default value                               */
}
CONFIG_FLOAT;

/****** Config String Entry *********************************************************************/
typedef struct
{
    const c8*   sect;               /* config entry section                                     */
    const c8*   key;                /* config entry key                                         */
    const c8*   def;                /* config entry default value                               */
}
CONFIG_STRING;

/********************************/
/*  Macro                       */
/********************************/
/****** Config Option ***************************************************************************/
#define CNFO_INT(   sect_, key_, def_)  &(const CONFIG_INT)    { .sect = sect_, .key = key_, .def = def_ }
#define CNFO_BOOL(  sect_, key_, def_)  &(const CONFIG_BOOL)   { .sect = sect_, .key = key_, .def = def_ }
#define CNFO_FLOAT( sect_, key_, def_)  &(const CONFIG_FLOAT)  { .sect = sect_, .key = key_, .def = def_ }
#define CNFO_STRING(sect_, key_, def_)  &(const CONFIG_STRING) { .sect = sect_, .key = key_, .def = def_ }

/********************************/
/*  Internal Headers            */
/********************************/
/****** Config Defs *****************************************************************************/
#include <cnf_def.h>                /* config def                                               */

/********************************/
/*  Prototypes                  */
/********************************/
/****** Save ************************************************************************/
/*
*   Description
*     Save Config file.
*/
void    CNF_Save( void );

/****** Get *************************************************************************/
/*
*   Description:
*     Get a config setting via config definition struct.
*
*   Parameters:
*     - pCnfDef : pointer to a config setting definition
*
*   Returns:
*     The user setting if it exists. If not, the default value
*/
i32       CNF_GetInt(    const CONFIG_INT*    pCnfDef );
f64       CNF_GetFloat(  const CONFIG_FLOAT*  pCnfDef );
bool      CNF_GetBool(   const CONFIG_BOOL*   pCnfDef );
const c8* CNF_GetString( const CONFIG_STRING* pCnfDef );

/****** Set *************************************************************************/
/*
*   Description:
*     Set a config setting via config definition struct.
*
*   Parameters:
*     - pCnfDef : pointer to a config setting definition
*     - val     : value to set
*/
void    CNF_SetInt(    const CONFIG_INT*    pCnfDef, i32       val );
void    CNF_SetFloat(  const CONFIG_FLOAT*  pCnfDef, f64       val );
void    CNF_SetBool(   const CONFIG_BOOL*   pCnfDef, bool      val );
void    CNF_SetString( const CONFIG_STRING* pCnfDef, const c8* val );

/****** Direct Get ******************************************************************/
/*
*   Description:
*     Get a config setting via direct config parameters.
*
*   Parameters:
*     - section : section to search in
*     - key     : key to find
*     - def     : default value
*
*   Returns:
*     The user setting if it exists. If not, the default value
*/
i32       CNF_DirectGetInt(    const c8* uSect, const c8* uKey, i32       def );
f64       CNF_DirectGetFloat(  const c8* uSect, const c8* uKey, f64       def );
bool      CNF_DirectGetBool(   const c8* uSect, const c8* uKey, bool      def );
const c8* CNF_DirectGetString( const c8* uSect, const c8* uKey, const c8* def );

/****** Direct Set ******************************************************************/
/*
*   Description:
*     Set a config setting via direct config parameters.
*
*   Parameters:
*     - section : section to search in
*     - key     : key to find
*     - val     : value to set
*/
void    CNF_DirectSetInt(    const c8* uSect, const c8* uKey, i32        val );
void    CNF_DirectSetFloat(  const c8* uSect, const c8* uKey, f64        val );
void    CNF_DirectSetBool(   const c8* uSect, const c8* uKey, bool       val );
void    CNF_DirectSetString( const c8* uSect, const c8* uKey, const c8*  val );

EXTERN_END

#endif/*H_CNF_CORE*/
