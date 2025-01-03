/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */

/****** Utility *********************************************************************/
#include <sa2b/util/endian.h> /* swapendian                                         */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */

/****** Self ************************************************************************/
#include <rf_draw/rfd_internal.h> /* parent & siblings                              */
#include <rf_draw/rfd_cnk.h>      /* chunk util                                     */

/************************/
/*  Game Functions      */
/************************/
/****** Shape ***********************************************************************/
#define ShapeCalcVList          FUNC_PTR(void, __cdecl, (const NJS_CNK_MODEL*, Sint32**, int), 0x00783990)
#define ShapeLinkCalcVList      FUNC_PTR(void, __cdecl, (const NJS_CNK_MODEL*, Sint32**, int), 0x007856A0)

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
njGetMotionLinearKeys(const void* key, int KeySize, int nbkeys, Float frame, const void* pKey1, const void *pKey2, Float *pRate)
{
    static const void* const fptr = (void*)0x0042C2C0;

    __asm
    {
        push [pRate]
        push [pKey2]
        push [pKey1]
        push [frame]
        push [nbkeys]
        mov esi, [key]
        mov edi, [KeySize]
        call fptr
        add esp, 20
    }
}

/****** Extern **********************************************************************/
void
rjShapeIntLinearVlist(const NJS_MKEY_P *VertexKey, int VertexNbKeys, const NJS_MKEY_P *NormalKey, int NormalNbKeys, Float frame, const Sint32 *SrcVlist, Sint32** pDstVlist, int byteswap)
{
    const Float* vtx_list1;
    const Float* vtx_list2;
    Float        vtx_ratio1;
    Float        vtx_ratio2;

    if ( VertexKey )
    {
        NJS_MKEY_P* vtx_key1;
        NJS_MKEY_P* vtx_key2;

        njGetMotionLinearKeys(VertexKey, sizeof(*VertexKey), VertexNbKeys, frame, &vtx_key1, &vtx_key2, &vtx_ratio1);

        vtx_ratio2 = 1.f - vtx_ratio1;

        vtx_list1 = vtx_key1->key;
        vtx_list2 = vtx_key2->key;
    }

    const Float* nrm_list1;
    const Float* nrm_list2;
    Float        nrm_ratio1;
    Float        nrm_ratio2;

    if ( NormalKey )
    {
        NJS_MKEY_P* nrm_key1;
        NJS_MKEY_P* nrm_key2;

        njGetMotionLinearKeys(NormalKey, sizeof(*NormalKey), NormalNbKeys, frame, &nrm_key1, &nrm_key2, &nrm_ratio1);

        nrm_ratio2 = 1.f - nrm_ratio1;

        nrm_list1 = nrm_key1->key;
        nrm_list2 = nrm_key2->key;
    }

    const Uint32* src_cnk_base = (const Uint32*)SrcVlist;
    Uint32*       dst_ptr      = (Uint32*)_nj_shape_buf_;

    *pDstVlist = (Sint32*)dst_ptr;

    for ( ; ; )
    {
        const CNK_VERTEX_HEAD* cnk_head = (const void*)src_cnk_base;

        const Sint32 cnk_type    = cnk_head->head;
        const Sint32 cnk_size    = cnk_head->size;
        const Sint32 cnk_indeces = cnk_head->nbindeces;

        const Uint32* src_ptr = src_cnk_base;

        if ( cnk_type == NJD_CE )
        {
            *dst_ptr = *src_ptr;
            break;
        }

        /** Get vertex chunk attributes **/
        bool has_vtx;
        bool has_nrm;
        bool has_col;
        bool has_flg;

        switch ( cnk_type ) {
        case NJD_CV:
            has_vtx = true;
            has_nrm = false;
            has_col = false;
            has_flg = false;
            break;

        case NJD_CV_D8:
            has_vtx = true;
            has_nrm = false;
            has_col = true;
            has_flg = false;
            break;

        case NJD_CV_UF:
        case NJD_CV_NF:
            has_vtx = true;
            has_nrm = false;
            has_col = false;
            has_flg = true;
            break;

        case NJD_CV_VN:
            has_vtx = true;
            has_nrm = true;
            has_col = false;
            has_flg = false;
            break;

        case NJD_CV_VN_D8:
            has_vtx = true;
            has_nrm = true;
            has_col = true;
            has_flg = false;
            break;

        case NJD_CV_VN_UF:
        case NJD_CV_VN_NF:
            has_vtx = true;
            has_nrm = true;
            has_col = false;
            has_flg = true;
            break;

        default:
            has_vtx = false;
            has_nrm = false;
            has_col = false;
            has_flg = false;
            break;
        }

        /** Copy vertex chunk header info **/
        *dst_ptr++ = *src_ptr++;
        *dst_ptr++ = *src_ptr++;

        /** Begin create vertex list and copy attr **/
        for (int vidx = 0; vidx < cnk_indeces; ++vidx)
        {
            if ( has_vtx )
            {
                if ( VertexKey )
                {
                    Float vtx10, vtx11, vtx12; // list1
                    Float vtx20, vtx21, vtx22; // list2

                    vtx10 = *vtx_list1++;
                    vtx11 = *vtx_list1++;
                    vtx12 = *vtx_list1++;

                    vtx20 = *vtx_list2++;
                    vtx21 = *vtx_list2++;
                    vtx22 = *vtx_list2++;

                    if (byteswap)
                    {
                        EndianSwap32(&vtx10);
                        EndianSwap32(&vtx11);
                        EndianSwap32(&vtx12);

                        EndianSwap32(&vtx20);
                        EndianSwap32(&vtx21);
                        EndianSwap32(&vtx22);
                    }

                    *(Float*)( &dst_ptr[0] ) = ( (vtx10 * vtx_ratio2) + (vtx20 * vtx_ratio1) );
                    *(Float*)( &dst_ptr[1] ) = ( (vtx11 * vtx_ratio2) + (vtx21 * vtx_ratio1) );
                    *(Float*)( &dst_ptr[2] ) = ( (vtx12 * vtx_ratio2) + (vtx22 * vtx_ratio1) );

                    dst_ptr += 3;
                    src_ptr += 3;
                }
                else
                {
                    *dst_ptr++ = *src_ptr++;
                    *dst_ptr++ = *src_ptr++;
                    *dst_ptr++ = *src_ptr++;
                }
            }

            if ( has_nrm )
            {
                if ( NormalKey )
                {
                    Float nrm10, nrm11, nrm12; // list1
                    Float nrm20, nrm21, nrm22; // list2

                    nrm10 = *nrm_list1++;
                    nrm11 = *nrm_list1++;
                    nrm12 = *nrm_list1++;

                    nrm20 = *nrm_list2++;
                    nrm21 = *nrm_list2++;
                    nrm22 = *nrm_list2++;

                    if (byteswap)
                    {
                        EndianSwap32(&nrm10);
                        EndianSwap32(&nrm11);
                        EndianSwap32(&nrm12);

                        EndianSwap32(&nrm20);
                        EndianSwap32(&nrm21);
                        EndianSwap32(&nrm22);
                    }

                    *(Float*)( &dst_ptr[0] ) = ( (nrm10 * nrm_ratio2) + (nrm20 * nrm_ratio1) );
                    *(Float*)( &dst_ptr[1] ) = ( (nrm11 * nrm_ratio2) + (nrm21 * nrm_ratio1) );
                    *(Float*)( &dst_ptr[2] ) = ( (nrm12 * nrm_ratio2) + (nrm22 * nrm_ratio1) );

                    dst_ptr += 3;
                    src_ptr += 3;
                }
                else
                {
                    *dst_ptr++ = *src_ptr++;
                    *dst_ptr++ = *src_ptr++;
                    *dst_ptr++ = *src_ptr++;
                }
            }

            if ( has_col )
                *dst_ptr++ = *src_ptr++;

            if ( has_flg )
                *dst_ptr++ = *src_ptr++;
        }

        src_cnk_base += 1 + cnk_size;
    }
}

__declspec(naked)
void
___ShapeIntLinearVlist(void)
{
    __asm
    {
        push [esp+28] // byteswap
        push [esp+28] // pDstVlist
        push eax     // SrcVlist
        push [esp+32] // frame
        push [esp+32] // NormalNbKeys
        push [esp+32] // NormalKey
        push [esp+32] // VertexNbKeys
        push [esp+32] // VertexKey
        call rjShapeIntLinearVlist
        add esp, 32
        retn
    }
}

void
rjShapeLinkIntLinearVlist(const NJS_MKEY_P *Vertex1Key, int Vertex1NbKeys, const NJS_MKEY_P *Normal1Key, int Normal1NbKeys, Float frame1,
                          const NJS_MKEY_P *Vertex2Key, int Vertex2NbKeys, const NJS_MKEY_P *Normal2Key, int Normal2NbKeys, Float frame2,
                          const Float rate, const Sint32 *SrcVlist, Sint32** pDstVlist, int byteswap)
{
    const Float inv_rate = 1.f - rate;

    const Float* vtx1_list1;
    const Float* vtx1_list2;
    Float        vtx1_ratio1;
    Float        vtx1_ratio2;

    if ( Vertex1Key )
    {
        NJS_MKEY_P* vtx_key1;
        NJS_MKEY_P* vtx_key2;

        njGetMotionLinearKeys(Vertex1Key, sizeof(*Vertex1Key), Vertex1NbKeys, frame1, &vtx_key1, &vtx_key2, &vtx1_ratio1);

        vtx1_ratio2 = 1.f - vtx1_ratio1;

        vtx1_list1 = vtx_key1->key;
        vtx1_list2 = vtx_key2->key;
    }

    const Float* nrm1_list1;
    const Float* nrm1_list2;
    Float        nrm1_ratio1;
    Float        nrm1_ratio2;

    if ( Normal1Key )
    {
        NJS_MKEY_P* nrm_key1;
        NJS_MKEY_P* nrm_key2;

        njGetMotionLinearKeys(Normal1Key, sizeof(*Normal1Key), Normal1NbKeys, frame1, &nrm_key1, &nrm_key2, &nrm1_ratio1);

        nrm1_ratio2 = 1.f - nrm1_ratio1;

        nrm1_list1 = nrm_key1->key;
        nrm1_list2 = nrm_key2->key;
    }

    const Float* vtx2_list1;
    const Float* vtx2_list2;
    Float        vtx2_ratio1;
    Float        vtx2_ratio2;

    if ( Vertex2Key )
    {
        NJS_MKEY_P* vtx_key1;
        NJS_MKEY_P* vtx_key2;

        njGetMotionLinearKeys(Vertex2Key, sizeof(*Vertex2Key), Vertex2NbKeys, frame2, &vtx_key1, &vtx_key2, &vtx2_ratio1);

        vtx2_ratio2 = 1.f - vtx2_ratio1;

        vtx2_list1 = vtx_key1->key;
        vtx2_list2 = vtx_key2->key;
    }

    const Float* nrm2_list1;
    const Float* nrm2_list2;
    Float        nrm2_ratio1;
    Float        nrm2_ratio2;

    if ( Normal2Key )
    {
        NJS_MKEY_P* nrm_key1;
        NJS_MKEY_P* nrm_key2;

        njGetMotionLinearKeys(Normal2Key, sizeof(*Normal2Key), Normal2NbKeys, frame2, &nrm_key1, &nrm_key2, &nrm2_ratio1);

        nrm2_ratio2 = 1.f - nrm2_ratio1;

        nrm2_list1 = nrm_key1->key;
        nrm2_list2 = nrm_key2->key;
    }

    const Uint32* src_cnk_base = (const Uint32*)SrcVlist;
    Uint32*       dst_ptr      = (Uint32*)_nj_shape_buf_;

    *pDstVlist = (Sint32*)dst_ptr;

    for ( ; ; )
    {
        const CNK_VERTEX_HEAD* cnk_head = (const void*)src_cnk_base;

        const Sint32 cnk_type    = cnk_head->head;
        const Sint32 cnk_size    = cnk_head->size;
        const Sint32 cnk_indeces = cnk_head->nbindeces;

        const Uint32* src_ptr = src_cnk_base;

        if ( cnk_type == NJD_CE )
        {
            *dst_ptr = *src_ptr;
            break;
        }

        /** Get vertex chunk attributes **/
        bool has_vtx;
        bool has_nrm;
        bool has_col;
        bool has_flg;

        switch ( cnk_type ) {
            case NJD_CV:
                has_vtx = true;
                has_nrm = false;
                has_col = false;
                has_flg = false;
                break;

            case NJD_CV_D8:
                has_vtx = true;
                has_nrm = false;
                has_col = true;
                has_flg = false;
                break;

            case NJD_CV_UF:
            case NJD_CV_NF:
                has_vtx = true;
                has_nrm = false;
                has_col = false;
                has_flg = true;
                break;

            case NJD_CV_VN:
                has_vtx = true;
                has_nrm = true;
                has_col = false;
                has_flg = false;
                break;

            case NJD_CV_VN_D8:
                has_vtx = true;
                has_nrm = true;
                has_col = true;
                has_flg = false;
                break;

            case NJD_CV_VN_UF:
            case NJD_CV_VN_NF:
                has_vtx = true;
                has_nrm = true;
                has_col = false;
                has_flg = true;
                break;

            default:
                has_vtx = false;
                has_nrm = false;
                has_col = false;
                has_flg = false;
                break;
        }

        /** Copy vertex chunk header info **/
        *dst_ptr++ = *src_ptr++;
        *dst_ptr++ = *src_ptr++;

        /** Begin create vertex list and copy attr **/
        for (int vidx = 0; vidx < cnk_indeces; ++vidx)
        {
            if ( has_vtx )
            {
                Float vtx1[3];
                Float vtx2[3];

                if ( Vertex1Key )
                {
                    Float vtx10, vtx11, vtx12; // list1
                    Float vtx20, vtx21, vtx22; // list2

                    vtx10 = *vtx1_list1++;
                    vtx11 = *vtx1_list1++;
                    vtx12 = *vtx1_list1++;

                    vtx20 = *vtx1_list2++;
                    vtx21 = *vtx1_list2++;
                    vtx22 = *vtx1_list2++;

                    if (byteswap)
                    {
                        EndianSwap32(&vtx10);
                        EndianSwap32(&vtx11);
                        EndianSwap32(&vtx12);

                        EndianSwap32(&vtx20);
                        EndianSwap32(&vtx21);
                        EndianSwap32(&vtx22);
                    }

                    vtx1[0] = ( (vtx10 * vtx1_ratio2) + (vtx20 * vtx1_ratio1) );
                    vtx1[1] = ( (vtx11 * vtx1_ratio2) + (vtx21 * vtx1_ratio1) );
                    vtx1[2] = ( (vtx12 * vtx1_ratio2) + (vtx22 * vtx1_ratio1) );
                }
                else
                {
                    vtx1[0] = *(Float*)( &src_ptr[0] );
                    vtx1[1] = *(Float*)( &src_ptr[1] );
                    vtx1[2] = *(Float*)( &src_ptr[2] );
                }

                if ( Vertex2Key )
                {
                    Float vtx10, vtx11, vtx12; // list1
                    Float vtx20, vtx21, vtx22; // list2

                    vtx10 = *vtx2_list1++;
                    vtx11 = *vtx2_list1++;
                    vtx12 = *vtx2_list1++;

                    vtx20 = *vtx2_list2++;
                    vtx21 = *vtx2_list2++;
                    vtx22 = *vtx2_list2++;

                    if (byteswap)
                    {
                        EndianSwap32(&vtx10);
                        EndianSwap32(&vtx11);
                        EndianSwap32(&vtx12);

                        EndianSwap32(&vtx20);
                        EndianSwap32(&vtx21);
                        EndianSwap32(&vtx22);
                    }

                    vtx2[0] = ( (vtx10 * vtx1_ratio2) + (vtx20 * vtx1_ratio1) );
                    vtx2[1] = ( (vtx11 * vtx1_ratio2) + (vtx21 * vtx1_ratio1) );
                    vtx2[2] = ( (vtx12 * vtx1_ratio2) + (vtx22 * vtx1_ratio1) );
                }
                else
                {
                    vtx2[0] = *(Float*)( &src_ptr[0] );
                    vtx2[1] = *(Float*)( &src_ptr[1] );
                    vtx2[2] = *(Float*)( &src_ptr[2] );
                }

                *(Float*)( &dst_ptr[0] ) = ( (vtx1[0] * inv_rate) + (vtx2[0] * rate) );
                *(Float*)( &dst_ptr[1] ) = ( (vtx1[1] * inv_rate) + (vtx2[1] * rate) );
                *(Float*)( &dst_ptr[2] ) = ( (vtx1[2] * inv_rate) + (vtx2[2] * rate) );

                dst_ptr += 3;
                src_ptr += 3;
            }

            if ( has_nrm )
            {
                Float nrm1[3];
                Float nrm2[3];

                if ( Normal1Key )
                {
                    Float nrm10, nrm11, nrm12; // list1
                    Float nrm20, nrm21, nrm22; // list2

                    nrm10 = *nrm1_list1++;
                    nrm11 = *nrm1_list1++;
                    nrm12 = *nrm1_list1++;

                    nrm20 = *nrm1_list2++;
                    nrm21 = *nrm1_list2++;
                    nrm22 = *nrm1_list2++;

                    if (byteswap)
                    {
                        EndianSwap32(&nrm10);
                        EndianSwap32(&nrm11);
                        EndianSwap32(&nrm12);

                        EndianSwap32(&nrm20);
                        EndianSwap32(&nrm21);
                        EndianSwap32(&nrm22);
                    }

                    nrm1[0] = ( (nrm10 * nrm1_ratio2) + (nrm20 * nrm1_ratio1) );
                    nrm1[1] = ( (nrm11 * nrm1_ratio2) + (nrm21 * nrm1_ratio1) );
                    nrm1[2] = ( (nrm12 * nrm1_ratio2) + (nrm22 * nrm1_ratio1) );
                }
                else
                {
                    nrm1[0] = *(Float*)( &src_ptr[0] );
                    nrm1[1] = *(Float*)( &src_ptr[1] );
                    nrm1[2] = *(Float*)( &src_ptr[2] );
                }

                if ( Normal2Key )
                {
                    Float nrm10, nrm11, nrm12; // list1
                    Float nrm20, nrm21, nrm22; // list2

                    nrm10 = *nrm2_list1++;
                    nrm11 = *nrm2_list1++;
                    nrm12 = *nrm2_list1++;

                    nrm20 = *nrm2_list2++;
                    nrm21 = *nrm2_list2++;
                    nrm22 = *nrm2_list2++;

                    if (byteswap)
                    {
                        EndianSwap32(&nrm10);
                        EndianSwap32(&nrm11);
                        EndianSwap32(&nrm12);

                        EndianSwap32(&nrm20);
                        EndianSwap32(&nrm21);
                        EndianSwap32(&nrm22);
                    }

                    nrm2[0] = ( (nrm10 * nrm1_ratio2) + (nrm20 * nrm1_ratio1) );
                    nrm2[1] = ( (nrm11 * nrm1_ratio2) + (nrm21 * nrm1_ratio1) );
                    nrm2[2] = ( (nrm12 * nrm1_ratio2) + (nrm22 * nrm1_ratio1) );
                }
                else
                {
                    nrm2[0] = *(Float*)( &src_ptr[0] );
                    nrm2[1] = *(Float*)( &src_ptr[1] );
                    nrm2[2] = *(Float*)( &src_ptr[2] );
                }

                *(Float*)( &dst_ptr[0] ) = ( (nrm1[0] * inv_rate) + (nrm2[0] * rate) );
                *(Float*)( &dst_ptr[1] ) = ( (nrm1[1] * inv_rate) + (nrm2[1] * rate) );
                *(Float*)( &dst_ptr[2] ) = ( (nrm1[2] * inv_rate) + (nrm2[2] * rate) );

                dst_ptr += 3;
                src_ptr += 3;
            }

            if ( has_col )
                *dst_ptr++ = *src_ptr++;

            if ( has_flg )
                *dst_ptr++ = *src_ptr++;
        }

        src_cnk_base += 1 + cnk_size;
    }
}

void
rjCnkPushPopShape(const NJS_CNK_OBJECT* cnkobj, int bBE)
{
    do
    {
        njPushMatrixEx();

        njMotionTransformEx(cnkobj);

        if (_nj_cnk_motion_callback_)
            _nj_cnk_motion_callback_((void*)cnkobj);

        const Uint32   eval  = cnkobj->evalflags;
        NJS_CNK_MODEL* model = (void*)cnkobj->model;

        if (eval & NJD_EVAL_SHAPE_SKIP)
        {
            if (model && !(eval & NJD_EVAL_HIDE))
                _nj_obj_motion_info_[0].draw_func_p((void*)model);
        }
        else
        {
            if (model && !(eval & NJD_EVAL_HIDE))
            {
                Sint32* shp_vlist;

                ShapeCalcVList(model, &shp_vlist, bBE);

                njSetNextShapeNodeEx();

                Sint32* const old_vlist = model->vlist;

                model->vlist = shp_vlist;

                _nj_obj_motion_info_[0].draw_func_p(model);

                model->vlist = old_vlist;
            }
            else
                njSetNextShapeNodeEx();
        }

        if (cnkobj->child)
            rjCnkPushPopShape(cnkobj->child, bBE);

        njPopMatrixEx();

        cnkobj = cnkobj->sibling;
    }
    while (cnkobj);
}

void
rjCnkPushPopShapeLink(const NJS_CNK_OBJECT* cnkobj, int bBE)
{
    do
    {
        njPushMatrixEx();

        njMotionLinkTransformEx(cnkobj);

        if (_nj_cnk_motion_callback_)
            _nj_cnk_motion_callback_((void*)cnkobj);

        const Uint32   eval  = cnkobj->evalflags;
        NJS_CNK_MODEL* model = (void*)cnkobj->model;

        if (eval & NJD_EVAL_SHAPE_SKIP)
        {
            if (model && !(eval & NJD_EVAL_HIDE))
                _nj_obj_motion_info_[0].draw_func_p((void*)model);
        }
        else
        {
            if (model && !(eval & NJD_EVAL_HIDE))
            {
                Sint32* shp_vlist;

                ShapeLinkCalcVList(model, &shp_vlist, bBE);

                njSetNextShapeLinkNode();

                Sint32* const old_vlist = model->vlist;

                model->vlist = shp_vlist;

                _nj_obj_motion_info_[0].draw_func_p(model);

                model->vlist = old_vlist;
            }
            else
                njSetNextShapeLinkNode();
        }

        if (cnkobj->child)
            rjCnkPushPopShapeLink(cnkobj->child, bBE);

        njPopMatrixEx();

        cnkobj = cnkobj->sibling;
    }
    while (cnkobj);
}
