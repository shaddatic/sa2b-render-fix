/*
*   SA2 Render Fix - '/rf_config/rfcnf_sect.h'
*
*   Description:
*       Render Fix config setting sections.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_CONFIG_SECT_H_
#define _RF_CONFIG_SECT_H_

/************************/
/*  Constants           */
/************************/
/****** Config sections *****************************************************/
/** Main **/
#define CNFS_GLOBAL         "main"
#define CNFS_SHADOW         "shadows"
#define CNFS_COMMON         "common"

/** Menus **/
#define CNFS_MENUS          "m_menus"
#define CNFS_EGET           "eget"

/** Stages **/
#define CNFS_FG             "w_jungle"
#define CNFS_CE             "c_escape"
#define CNFS_AM             "a_mine"
#define CNFS_CC             "c_core"

/** Bosses **/
#define CNFS_BBOGY          "bossbogy"

/** Other **/
#define CNFS_CART           "cart"
#define CNFS_EVENT          "event"

/** Experimental **/
#define CNFS_EXP            "experimental"

/** Debug **/
#define CNFS_DEBUG          "debug"

/** Hidden **/
#define CNFS_HIDDEN         "internal"

#endif/*_RF_CONFIG_SECT_H_*/
