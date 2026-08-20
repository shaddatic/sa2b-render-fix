#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/writeop.h>

/****** Utl *************************************************************************************/
#include <samt/util/asm.h>          /* asm helper                                               */

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/player.h>
#include <samt/sonic/debug.h>

/** Render Fix **/
#include <rf_core.h>                /* core                                                     */
#include <rf_model.h>
#include <rf_ninja.h>
#include <rf_njcnk.h>               /* ninja chunk draw                                         */
#include <rf_shadow.h>

/** RF Util **/
#include <rfu_draw.h>

#define mtx_BoardCE     DATA_REF(NJS_MATRIX, 0x01A282F8)
#define mtx_BoardMH     DATA_REF(NJS_MATRIX, 0x01A513B0)

ASM_FUNC
static void
BoardGetAttributes(uintptr_t* ppUnk, NJS_TEXLIST** ppTexList, NJS_CNK_OBJECT** ppObject, int pno)
{
    // save regs
    ASM_PUSH( ebx );

    // arguments
    ASM_PUSH(      ASM_ESP(4+0 +1) ); // pno
    ASM_MOVE( ecx, ASM_ESP(3+1 +1) ); // ppObject
    ASM_MOVE( edx, ASM_ESP(2+1 +1) ); // ppTexList
    ASM_MOVE( eax, ASM_ESP(1+1 +1) ); // ppUnk

    // call
    ASM_CALL_R( ebx, 0x005EBBC0 );

    // end aguments
    ASM_ESP_ADD( 1 );

    // pull regs
    ASM_POP( ebx );

    // return
    ASM_RET( 0 );
}

void
ObjectBoardShadow_CE(task* tp)
{
    taskwk* const twp = tp->twp;

    playerwk* pwp = playerpwp[twp->smode];

    if (!pwp)
        return;

    NJS_CNK_OBJECT* p_object;
    NJS_TEXLIST* p_texlist;
    uintptr_t p_unk;

    BoardGetAttributes(&p_unk, &p_texlist, &p_object, twp->smode);

    njCnkSetMotionCallback((void*)0x005EBCC0);

    njPushMatrixEx();

    if (twp->mode != 1)
    {
        njTranslateEx(&twp->pos);
        njRotateZ(NULL, twp->ang.z);
        njRotateX(NULL, twp->ang.x);
        njRotateY(NULL, twp->ang.y);

        njRotateZ(NULL, p_object->ang[2]);
        njRotateY(NULL, p_object->ang[1]);
        njRotateX(NULL, p_object->ang[0]);

        njGetMatrix(&mtx_BoardCE);
    }
    else
    {
        uint32_t v11 = *(uint32_t*)((uintptr_t)tp->mwp + 24) + 24;

        NJS_MOTION* p_motion = plmotions[pwp->m.action + 24].mot;

        if (p_motion)
        {
            njTranslateEx(&twp->pos);
            njRotateZ(NULL, twp->ang.z);
            njRotateX(NULL, twp->ang.x);
            njRotateY(NULL, twp->ang.y);

            if (pwp->m.mtnmode == 2)
            {
                if (v11 - 145 > 0x17)
                {
                    njRotateZ(NULL, p_object->ang[2]);
                    njRotateY(NULL, p_object->ang[1]);
                    njRotateX(NULL, p_object->ang[0]);

                    njGetMatrix(&mtx_BoardCE);
                }
                else
                {
                    NJS_MOTION_LINK motion_link;

                    motion_link.motion[0] = plmotions[v11].mot;
                    motion_link.frame[0] = *(float*)((uintptr_t)tp->mwp + 28);

                    motion_link.motion[1] = p_motion;
                    motion_link.frame[1] = 0.0f;

                    njCnkAnimateMotionLink(p_object, &motion_link, pwp->m.nframe);
                }
            }
            else
            {
                njCnkAnimateMotion(p_object, p_motion, pwp->m.nframe);
            }
        }
    }

    njSetMatrix(NULL, &mtx_BoardCE);

    njCnkSetMotionCallback(NULL);

    njCnkModDrawObject(object_ce_board_mod);

    njPopMatrixEx();
}

#define object_board_mh     DATA_ARY(NJS_CNK_OBJECT, 0x00AE79A4, [1])

void
ObjectBoardShadow_MH(task* tp)
{
    taskwk* const twp = tp->twp;

    playerwk* pwp = playerpwp[twp->smode];

    if (!pwp)
        return;

    njCnkSetMotionCallback((void*)0x006F7BC0);

    njPushMatrixEx();

    if (twp->mode != 1)
    {
        njTranslateEx(&twp->pos);
        njRotateZ(NULL, twp->ang.z);
        njRotateX(NULL, twp->ang.x);
        njRotateY(NULL, twp->ang.y);

        njRotateZ(NULL, object_board_mh->ang[2]);
        njRotateY(NULL, object_board_mh->ang[1]);
        njRotateX(NULL, object_board_mh->ang[0]);

        njGetMatrix(&mtx_BoardMH);
    }
    else
    {
        uint32_t v11 = *(uint32_t*)((uintptr_t)tp->mwp + 24) + 24;

        NJS_MOTION* p_motion = plmotions[pwp->m.action + 24].mot;

        if (p_motion)
        {
            njTranslateEx(&twp->pos);
            njRotateZ(NULL, twp->ang.z);
            njRotateX(NULL, twp->ang.x);
            njRotateY(NULL, 0x4000 + twp->ang.y);

            if (pwp->m.mtnmode == 2)
            {
                if (v11 - 145 > 0x17)
                {
                    njRotateZ(NULL, object_board_mh->ang[2]);
                    njRotateY(NULL, object_board_mh->ang[1]);
                    njRotateX(NULL, object_board_mh->ang[0]);

                    njGetMatrix(&mtx_BoardMH);
                }
                else
                {
                    NJS_MOTION_LINK motion_link;

                    motion_link.motion[0] = plmotions[v11].mot;
                    motion_link.frame[0] = *(float*)((uintptr_t)tp->mwp + 28);

                    motion_link.motion[1] = p_motion;
                    motion_link.frame[1] = 0.0f;

                    njCnkAnimateMotionLink(object_board_mh, &motion_link, pwp->m.nframe);
                }
            }
            else
            {
                njCnkAnimateMotion(object_board_mh, p_motion, pwp->m.nframe);
            }
        }
    }

    njSetMatrix(NULL, &mtx_BoardMH);

    njCnkSetMotionCallback(NULL);

    njCnkModDrawObject(object_mh_board_mod);

    njPopMatrixEx();
}

void
ObjectBoardHook_MH(task* tp)
{
    tp->twp->smode = tp->twp->ang.x & 1;
    tp->exec = (void*)0x006F7AF0;
    tp->dest = (void*)0x006FE430;
    tp->disp = (void*)0x006F7BE0;
    tp->disp_shad = ObjectBoardShadow_MH;
}

void
CHS_BoardInit(void)
{
    KillCall(0x005EBC9B);
    WriteJump(0x005EBFC0, ObjectBoardShadow_CE);
    WriteJump(0x006F7AC0, ObjectBoardHook_MH);
}
