/*
*   SA2 Render Fix - '/rfapi_chunk.h'
*
*   Description:
*     The 'Ninja Chunk' API module is for drawing Ninja Chunk objects and models.
* 
*   Notes:
*     - Many things, such as the Chunk Control flags, are extensions to the format made for
*       Render Fix, and weren't part of the original Ninja/Ninja2 API.
* 
*   Version History:
*     - v1.5.0.0        : Version 0, initial release
* 
*   Availability:
*     - Before Init     : No
*     - At Init         : Yes
*     - After Init      : Yes
*/
#ifndef H_RFAPI_CHUNK
#define H_RFAPI_CHUNK

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define RFAPI_CHUNK_VER             (0) /* chunk api version                                    */

/****** Chunk Control Flags *********************************************************************/
#define RJD_CNK_CTRL_OPAQUE         (1<< 0) /* draw opaque polygons                             */
#define RJD_CNK_CTRL_TRANSLUCENT    (1<< 1) /* draw translucent polygons                        */
#define RJD_CNK_CTRL_NORMAL         (1<< 2) /* draw normal polygon faces                        */
#define RJD_CNK_CTRL_INVERSE        (1<< 3) /* draw inverse polygon faces                       */
#define RJD_CNK_CTRL_VLIST          (1<< 4) /* execute vlist chunk data                         */
#define RJD_CNK_CTRL_PLIST          (1<< 5) /* execute plist chunk data                         */

#define RJD_CNK_CTRL_VNORM          (1<< 8) /* use vertex normal attributes                     */
#define RJD_CNK_CTRL_VCOLR          (1<< 9) /* use vertex color attributes                      */
#define RJD_CNK_CTRL_VSPEC          (1<<10) /* use vertex specular attributes                   */

#define RJD_CNK_CTRL_TEXTURE        (1<<12) /* use textures                                     */
#define RJD_CNK_CTRL_ENVIRONMENT    (1<<13) /* use normal-based environment calculations        */
#define RJD_CNK_CTRL_DBLIGHT        (1<<14) /* use double sided lighting when available         */

/****** Chunk Control Masks *********************************************************************/
#define RJD_CNK_CTRL_MASK_DRAW      (RJD_CNK_CTRL_OPAQUE|RJD_CNK_CTRL_TRANSLUCENT)
#define RJD_CNK_CTRL_MASK_CULL      (RJD_CNK_CTRL_NORMAL|RJD_CNK_CTRL_INVERSE)
#define RJD_CNK_CTRL_MASK_MODEL     (RJD_CNK_CTRL_VLIST|RJD_CNK_CTRL_PLIST)
#define RJD_CNK_CTRL_MASK_VTX       (RJD_CNK_CTRL_VNORM|RJD_CNK_CTRL_VCOLR|RJD_CNK_CTRL_VSPEC)
#define RJD_CNK_CTRL_MASK_EFFECT    (RJD_CNK_CTRL_TEXTURE|RJD_CNK_CTRL_ENVIRONMENT|RJD_CNK_CTRL_DBLIGHT)

#define RJD_CNK_CTRL_MASK           (RJD_CNK_CTRL_MASK_DRAW|RJD_CNK_CTRL_MASK_CULL|RJD_CNK_CTRL_MASK_MODEL|RJD_CNK_CTRL_MASK_VTX|RJD_CNK_CTRL_MASK_EFFECT)

/****** Chunk Strip Flags ***********************************************************************/
#define RJD_FST_EUA                 (0x80<<8) /* extended use alpha                             */

/****** Chunk Material Colors *******************************************************************/
typedef enum rjcnkmat
{
    RJ_CMC_DIFF,                    /* diffuse material color                                   */
    RJ_CMC_AMBI,                    /* ambient material color                                   */
    RJ_CMC_SPEC,                    /* specular material color                                  */

    RJ_NB_CMC,                      /* enum count                                               */
}
RJ_CNK_MATCOLOR;

/****** Chunk Material Flag *********************************************************************/
#define RJD_CMF_DIFF                (1<<0) /* has diffuse material color                        */
#define RJD_CMF_AMBI                (1<<1) /* has ambient material color                        */
#define RJD_CMF_SPEC                (1<<2) /* has specular material color                       */

/********************************/
/*  API Structures              */
/********************************/
/****** Chunk API *******************************************************************************/
typedef struct
{
    uint32_t version;               /* structure version                                        */

    /****** Version >= 0 ********************************************************************/

    /**** Chunk Control *************************************/
    /*
    *   Description:
    *     Set/unset Chunk draw control flags.
    *
    *   Parameters:
    *     - off_flag    : flags to be turned off/and'd                       [RJD_CNK_CTRL]
    *     - on_flag     : flags to be turned on/or'd                         [RJD_CNK_CTRL]
    */
    void (*CnkSetControl)( Uint32 off_flag, Uint32 on_flag );
    /*
    *   Description:
    *     Get the current Chunk draw control flags.
    */
    Uint32 (*CnkGetControl)( void );

    /**** Chunk Callback ************************************/
    /*
    *   Description:
    *     Set the Chunk model callback function.
    *
    *   Notes:
    *     - This is a Render Fix extension, and is not part of base Ninja.
    *     - Called for every *non-clipped* model drawn using any draw function.
    *     - Reset the callback to 'NULL' when drawing is complete.
    * 
    *   Parameters:
    *     - callback        : model callback function                        [opt: nullptr]
    *       - model         : callback model pointer
    */
    void (*CnkSetModelCallback)( void(*callback)(NJS_CNK_MODEL* model) );
    /*
    *   Description:
    *     Set the Chunk object callback function.
    *
    *   Notes:
    *     - This is a Render Fix extension, and is not part of base Ninja.
    *     - Called for every object drawn using 'CnkDrawObject'.
    *     - Reset the callback to 'NULL' when drawing is complete.
    * 
    *   Parameters:
    *     - callback        : object callback function                       [opt: nullptr]
    *       - object        : callback object pointer
    */
    void (*CnkSetObjectCallback)( void(*callback)(NJS_CNK_OBJECT* object) );
    /*
    *   Description:
    *     Set the Chunk motion callback function.
    *
    *   Notes:
    *     - Called for every object drawn using 'CnkDrawMotion' or its variants.
    *     - Reset the callback to 'NULL' when drawing is complete.
    * 
    *   Parameters:
    *     - callback        : object callback function                       [opt: nullptr]
    *       - object        : callback object pointer
    */
    void (*CnkSetMotionCallback)( void(*callback)(NJS_CNK_OBJECT* object) );

    /**** Chunk Polygon Callback ****************************/
    /*
    *   Description:
    *     Set the texture ID callback function, for texture animation.
    *
    *   Notes:
    *     - This is a Render Fix extension, and is not part of base Ninja.
    *     - The returned value will be used as the new texid.
    *     - Called for every 'tiny' chunk data in a drawn model.
    *     - Reset the callback to 'NULL' when drawing is complete.
    *
    *   Parameters:
    *     - callback        : texture callback function                              [opt: nullptr]
    *       - n             : texture index
    *       + return        : new texture index
    */
    void (*CnkSetTextureCallback)( Sint16(*callback)(Sint16 n) );
    /*
    *   Description:
    *     Set the Chunk material callback function, for changing material colors at draw time.
    * 
    *   Notes:
    *     - This is a Render Fix extension, and is not part of base Ninja.
    *     - The returned flags determines what colors will be applied to the model.
    *     - Called for every 'material' chunk data in a drawn model.
    *     - Reset the callback to 'NULL' when drawing is complete.
    *
    *   Parameters:
    *     - callback        : material callback function                             [opt: nullptr]
    *       - dst           : destination material color array                          [RJ_CMC_##]
    *       - src           : source material color array                               [RJ_CMC_##]
    *       - flag          : material color flags in this material chunk               [RJ_CMF_##]
    *       + return        : output material color flags, for adding material colors   [RJ_CMF_##]
    */
    void (*CnkSetMaterialCallback)( Uint32(*callback)(NJS_BGRA dst[RJ_NB_CMC], const NJS_BGRA src[RJ_NB_CMC], Uint32 flag) );

    /**** Chunk Modify **************************************/
    /*
    *   Description:
    *     Set the Chunk UV offset value for regular UVs, for texture scrolling.
    *
    *   Notes:
    *     - This is a Render Fix extension, and is not part of base Ninja; this is despite
    *       sharing a name with an actual Ninja function.
    *     - This will *not* affect environment maps.
    *     - Reset these values to '0.f' when drawing is complete.
    *
    *   Parameters:
    *     - u, v        : u and v scroll offset
    */
    void (*CnkSetUvScroll)( Float u, Float v );
    /*
    *   Description:
    *     Set the Chunk UV offset value for environment mapping, for texture scrolling.
    *   Scrolling only applies when 'NJD_CONTROL_3D_ENV_UV_SCROLL' is set.
    *
    *   Notes:
    *     - In base Ninja this is named 'njCnkSetUvScroll', but the functionality is otherwise
    *       the same.
    *     - Reset these values to '0.f' when drawing is complete.
    *
    *   Parameters:
    *     - u, v        : u and v scroll offset
    */
    void (*CnkSetEnvUvScroll)( Float u, Float v );

    /**** Chunk Draw ****************************************/
    /*
    *   Description:
    *     Draw a Chunk model normally, using all model parameters and features as expected.
    *
    *   Notes:
    *     - This is a Render Fix extension, and is not part of base Ninja; although Ninja had a
    *       type of 'Normal' draw, it wasn't referenced for this function.
    *
    *   Parameters:
    *     - model       : chunk model
    * 
    *   Returns:
    *     '0' on success; or '-1' if the model was clipped.
    */
    Sint32 (*CnkNormalDrawModel)( NJS_CNK_MODEL* model );
    /*
    *   Description:
    *     Draw a Chunk model with 'Easy' emulation, which is the fastest but most limited
    *   draw function. It lacks support for many Chunk features.
    *
    *   Parameters:
    *     - model       : chunk model
    * 
    *   Returns:
    *     '0' on success; or '-1' if the model was clipped.
    */
    Sint32 (*CnkEasyDrawModel)( NJS_CNK_MODEL* model );
    /*
    *   Description:
    *     Draw a Chunk model with 'Simple' emulation, which is the least limited draw
    *   function.
    *
    *   Parameters:
    *     - model       : chunk model
    * 
    *   Returns:
    *     '0' on success; or '-1' if the model was clipped.
    */
    Sint32 (*CnkSimpleDrawModel)( NJS_CNK_MODEL* model );
    /*
    *   Description:
    *     Draw a Chunk model with 'EasyMulti' emulation, which is the multi-light variant of
    *   the 'Easy' draw function.
    *
    *   Parameters:
    *     - model       : chunk model
    * 
    *   Returns:
    *     '0' on success; or '-1' if the model was clipped.
    */
    Sint32 (*CnkEasyMultiDrawModel)( NJS_CNK_MODEL* model );
    /*
    *   Description:
    *     Draw a Chunk model with 'SimpleMulti' emulation, which is the multi-light variant of
    *   the 'Simple' draw function.
    *
    *   Parameters:
    *     - model       : chunk model
    * 
    *   Returns:
    *     '0' on success; or '-1' if the model was clipped.
    */
    Sint32 (*CnkSimpleMultiDrawModel)( NJS_CNK_MODEL* model );
    /*
    *   Description:
    *     Draw a Chunk model as if it was compiled with 'njCnkDirectObjectCompile' and then
    *   drawn with 'njDirectDrawObject'.
    * 
    *   Notes:
    *     - This is a Render Fix extension, and is not part of base Ninja; although the
    *   behavior it emulates is.
    *
    *   Parameters:
    *     - model       : chunk model
    * 
    *   Returns:
    *     '0' on success; or '-1' if the model was clipped.
    */
    Sint32 (*CnkDirectDrawModel)( NJS_CNK_MODEL* model );
    /*
    *   Description:
    *     Draw a Chunk model as a modifier volume, usually for shadows.
    *
    *   Parameters:
    *     - model       : chunk model
    * 
    *   Returns:
    *     '0' on success; or '-1' if the model was clipped.
    */
    Sint32 (*CnkModDrawModel)( NJS_CNK_MODEL* model );

    /**** Chunk Object **************************************/
    /*
    *   Description:
    *     Transform a Chunk object tree, with model callback.
    * 
    *   Notes:
    *     - Calls 'Object' and 'Model' callback functions.
    *
    *   Parameters:
    *     - object      : chunk object head
    *     - callback    : model callback function (eg. CnkEasyDrawModel)
    *       - model     : chunk model
    *       + return    : clip status
    */
    void (*CnkTransformObject)( NJS_CNK_OBJECT* object, Sint32(*callback)(NJS_CNK_MODEL* model) );

    /**** Chunk Motion **************************************/
    /*
    *   Description:
    *     Transform a Chunk object with a motion, with model callback.
    * 
    *   Notes:
    *     - Calls 'Motion' and 'Model' callback functions.
    *
    *   Parameters:
    *     - object      : chunk object head
    *     - motion      : motion structure
    *     - frame       : motion frame
    *     - callback    : model callback function
    */
    void (*CnkTransformMotion)( NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame, Sint32(*callback)(NJS_CNK_MODEL*) );
    /*
    *   Description:
    *     Transform a Chunk object with a motion link (interpolated motions), with model
    *   callback.
    * 
    *   Notes:
    *     - Calls 'Motion' and 'Model' callback functions.
    *
    *   Parameters:
    *     - object      : chunk object head
    *     - motion_link : motion link structure
    *     - rate        : motion ratio                                                    [0~1]
    *     - callback    : model callback function
    */
    void (*CnkTransformMotionLink)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float rate, Sint32(*callback)(NJS_CNK_MODEL*) );

    /**** Chunk Shape Motion ********************************/
    /*
    *   Description:
    *     Transform a Chunk object with a motion and shape motion, with model callback.
    * 
    *   Notes:
    *     - Calls 'Motion' and 'Model' callback functions.
    *     - If no shape motion is given, functions as 'CnkDrawMotion'
    *
    *   Parameters:
    *     - object      : chunk object head
    *     - motion      : motion structure
    *     - shape       : shape motion structure                                 [opt: nullptr]
    *     - frame       : motion frame
    *     - sframe      : shape motion frame (the normal functions re-use 'frame')
    *     - callback    : model callback function
    */
    void (*CnkTransformShapeMotion)( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame, Float sframe, Sint32(*callback)(NJS_CNK_MODEL*) );
    /*
    *   Description:
    *     Transform a Chunk object with a motion link and shape motion link (interpolated
    *   motions), with model callback.
    * 
    *   Notes:
    *     - Calls 'Motion' and 'Model' callback functions.
    *     - If no shape motion is given, functions as 'CnkDrawMotionLink'
    *
    *   Parameters:
    *     - object      : chunk object head
    *     - motion_link : motion link structure
    *     - shape_link  : shape motion link structure                            [opt: nullptr]
    *     - rate        : motion ratio                                                    [0~1]
    *     - callback    : model callback function
    */
    void (*CnkTransformShapeMotionLink)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, NJS_MOTION_LINK* shape_link, Float rate, Sint32(*callback)(NJS_CNK_MODEL*) );

    /**** Chunk Big Endian **********************************/
    /*
    *   Description:
    *     Transform a Chunk object with a motion and big endian shape motion.
    * 
    *   Notes:
    *     - Only the shape vertex data is big endian.
    */
    void (*CnkTransformShapeMotionBE)( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame, Float sframe, Sint32(*callback)(NJS_CNK_MODEL*) );
    /*
    *   Description:
    *     Transform a Chunk object with a motion link and big endian shape motion link.
    * 
    *   Notes:
    *     - Only the shape vertex data is big endian.
    */
    void (*CnkTransformShapeMotionLinkBE)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, NJS_MOTION_LINK* shape_link, Float rate, Sint32(*callback)(NJS_CNK_MODEL*) );
}
RFAPI_CHUNK;

#endif/*H_RFAPI_CHUNK*/
