/*
*   SA2 Render Fix - '/rf_config/rfcnf_enum.h'
*
*   Description:
*       Render Fix config setting enums.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_CONFIG_ENUM_H_
#define _RF_CONFIG_ENUM_H_

/************************/
/*  Enums               */
/************************/
/****** Basic Bool **********************************************************/
typedef enum
{
    CNFE_BOOL_DISABLED,
    CNFE_BOOL_ENABLED
}
CNFE_BOOL;

/****** Global Section ******************************************************/
/** Model tint fix mode **/
typedef enum
{
    CNFE_GLOBAL_MDLTINT_DISABLED,
    CNFE_GLOBAL_MDLTINT_DREAMCAST,
    CNFE_GLOBAL_MDLTINT_ENABLED,
}
CNFE_GLBL_MDLTINT;

/****** Shadows Section *****************************************************/
/** Cheap Shadow mode **/
typedef enum
{
    CNFE_SHADOW_CHSMD_DISABLED,
    CNFE_SHADOW_CHSMD_ULTRA_PERFORMANCE,
    CNFE_SHADOW_CHSMD_PERFORMANCE,
    CNFE_SHADOW_CHSMD_ENABLED,
}
CNFE_SHAD_CHSMD;

/** Global mode **/
typedef enum
{
    CNFE_SHADOW_GLMD_DISABLED,
    CNFE_SHADOW_GLMD_VANILLA,
    CNFE_SHADOW_GLMD_MODIFIER,
}
CNFE_SHAD_GLMD;

/** Player mode **/
typedef enum
{
    CNFE_SHADOW_PLMD_VANILLA,
    CNFE_SHADOW_PLMD_ENHANCED,
    CNFE_SHADOW_PLMD_EQUIPMENT,
    CNFE_SHADOW_PLMD_MODIFIER,
}
CNFE_SHAD_PLMD;

/** Shadow map resolution **/
typedef enum
{
    CNFE_SHADOW_RES_VERY_LOW,
    CNFE_SHADOW_RES_LOW,
    CNFE_SHADOW_RES_MEDIUM,
    CNFE_SHADOW_RES_HIGH,
    CNFE_SHADOW_RES_ULTRA,
    CNFE_SHADOW_RES_IMPERCEIVABLE
}
CNFE_SHAD_RES;

/** Shadow opacity **/
typedef enum
{
    CNFE_SHADOW_OPACITY_VANILLA,
    CNFE_SHADOW_OPACITY_DREAMCAST,
    CNFE_SHADOW_OPACITY_DREAMCAST_CHAO,
}
CNFE_SHAD_OPACITY;

#endif/*_RF_CONFIG_ENUM_H_*/
