/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */
#include <samt/ninja/njdef.h>       /* nja defs                                                 */

#pragma warning( push )
#pragma warning( disable : 4838 )    /* conversion from '$type' to '$type' requires a narrowing conversion */
#pragma warning( disable : 4309 )    /* 'initializing': truncation of constant value */

/********************************/
/*  Data                        */
/********************************/
/************************************************************************************************/
/*
*    Chunk Models
*/
/****** GUN Emblems *****************************************************************************/
#include <rf_nja/nja/e_kumi_emblem.nja>
#include <rf_nja/nja/e_g_kumi_emblem.nja>
#include <rf_nja/nja/e_b_kumi_emblem.nja>
#include <rf_nja/nja/e_gold_emblem.nja>
#include <rf_nja/nja/e_kyoko_emblem.nja>
#include <rf_nja/nja/e_shouko_wing_port.nja>
#include <rf_nja/nja/e_shouko_wing_starboard.nja>
#include <rf_nja/nja/e_shouko_aft.nja>
#include <rf_nja/nja/e_g_pathkumi_emblem.nja>
#include <rf_nja/nja/e_b_pathkumi_emblem.nja>
#include <rf_nja/nja/e_t_emi_emblem.nja>
#include <rf_nja/nja/e_a_emi_emblem.nja>
#include <rf_nja/nja/ce_truck_hood.nja>

/****** Amine Water *****************************************************************************/
#include <rf_nja/nja/minemizu.nja>

/****** Dreamcast AI Shield *********************************************************************/
#include <rf_nja/nja/e_s_ai_shield.nja>

/************************************************************************************************/
/*
*    Texlists
*/
/****** Jungle Object ***************************************************************************/
#include <rf_nja/tls/jo_tree.tls>

/****** Texture Error ***************************************************************************/
#include <rf_nja/tls/rf_texerr.tls>

#pragma warning( pop )
