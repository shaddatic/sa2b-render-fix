/*
*   dx9ctrl (SA2B) - '/dx9ctrl.h'
*
*   Description:
*     DirectX 9 control library for SA2PC core header.
*/
#ifndef H_DX9CTRL_INIT
#define H_DX9CTRL_INIT

DX9_HEADER_START

/************************/
/*  Prototypes          */
/************************/
/****** Init ************************************************************************************/
/*
*   Description:
*     Init DX9 Control library.
*/
void    DX9_Init( void );

/****** D3D9 Device *****************************************************************************/
/*
*   Description:
*     Get the DirectX9 device.
* 
*   Returns:
*     Pointer to the 'IDirect3DDevice9'.
*/
void*   DX9_GetDevice( void );

DX9_HEADER_END

#endif/*H_DX9CTRL_INIT*/
