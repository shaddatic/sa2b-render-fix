#pragma once

/*
*	Data References
*/

DataRef(float32, chOffsetAlpha, 0x01AED2D0);

/*
*	User Functions
*/

void chCnkDrawObject(NJS_CNK_OBJECT* object);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* chCnkDrawObject_p;

#endif