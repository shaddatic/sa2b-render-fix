/*
	Ninja Library
	
	COPYRIGHT (C) SEGA ENTERSRISES,LTD.
*/

#ifndef	_NJNJA_H_
#define	_NJNJA_H_

//#include <sg_xpt.h>				/* Contains Global Defines, sa2b/core.h already has these */
#include <sa2b/ninja/NinjaDef.h>
#include <sa2b/ninja/NinjaStr.h>
#include <sa2b/ninja/NinjaCnk.h>
#include <sa2b/ninja/NinjaVal.h>
#include <sa2b/ninja/NinjaApi.h>
#include <sa2b/ninja/NinjaPtcl.h>

#include <sa2b/ninja/Ginja.h>		/* Custom made for toolkit */
#include <sa2b/ninja/NinjaMisc.h>	/* ^ */

#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <sa2b/ninja/NinjaPad.h>

typedef union anyobj_p
{
	void*			ptr;
	NJS_OBJECT*		obj;
	NJS_CNK_OBJECT*	cnk;
	GJS_OBJECT*		gjs;
}
anyobj_p;

typedef struct 
{
	Angle x, y, z;
}
Angle3;

#endif
