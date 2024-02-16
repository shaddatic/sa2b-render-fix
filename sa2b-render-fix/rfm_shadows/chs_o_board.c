#include <sa2b/core.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/player.h>
#include <sa2b/src/debug.h>

/** Render Fix **/
#include <rf_file.h>
#include <rf_draw.h>

#define mtx_BoardCE     DataRef(NJS_MATRIX, 0x01A282F8)
#define mtx_BoardMH     DataRef(NJS_MATRIX, 0x01A513B0)

static NJS_CNK_OBJECT* object_o_board_mod;

static const void* const BoardGetAttributes_p = (void*)0x005EBBC0;

static void
BoardGetAttributes(uintptr_t* ppUnk, NJS_TEXLIST** ppTexList, NJS_CNK_OBJECT** ppObject, int pno)
{
    __asm
    {
        push[pno]
        mov ecx, [ppObject]
        mov edx, [ppTexList]
        mov eax, [ppUnk]

        call BoardGetAttributes_p

        add esp, 4
    }
}

static void
ObjectBoardCEDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    PLAYERWK* pwp = playerpwp[twp->smode];

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

        NJS_MOTION* p_motion = CHAR_MOTIONS[pwp->mj.mtnnum + 24].pMotion;

        if (p_motion)
        {
            njTranslateEx(&twp->pos);
            njRotateZ(NULL, twp->ang.z);
            njRotateX(NULL, twp->ang.x);
            njRotateY(NULL, twp->ang.y);

            if (pwp->mj.mtnmode == 2)
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

                    motion_link.motion[0] = CHAR_MOTIONS[v11].pMotion;
                    motion_link.frame[0] = *(float*)((uintptr_t)tp->mwp + 28);

                    motion_link.motion[1] = p_motion;
                    motion_link.frame[1] = 0.0f;

                    njCnkAnimateMotionLink(p_object, &motion_link, pwp->mj.nframe);
                }
            }
            else
            {
                njCnkAnimateMotion(p_object, p_motion, pwp->mj.nframe);
            }
        }
    }

    njSetMatrix(NULL, &mtx_BoardCE);

    njCnkSetMotionCallback(NULL);

    njCnkModDrawObject(object_o_board_mod);

    njPopMatrixEx();
}

#define object_board_mh     DataAry(NJS_CNK_OBJECT, 0x00AE79A4, [1])

void
ObjectBoardMHDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    PLAYERWK* pwp = playerpwp[twp->smode];

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

        NJS_MOTION* p_motion = CHAR_MOTIONS[pwp->mj.mtnnum + 24].pMotion;

        if (p_motion)
        {
            njTranslateEx(&twp->pos);
            njRotateZ(NULL, twp->ang.z);
            njRotateX(NULL, twp->ang.x);
            njRotateY(NULL, 0x4000 + twp->ang.y);

            if (pwp->mj.mtnmode == 2)
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

                    motion_link.motion[0] = CHAR_MOTIONS[v11].pMotion;
                    motion_link.frame[0] = *(float*)((uintptr_t)tp->mwp + 28);

                    motion_link.motion[1] = p_motion;
                    motion_link.frame[1] = 0.0f;

                    njCnkAnimateMotionLink(object_board_mh, &motion_link, pwp->mj.nframe);
                }
            }
            else
            {
                njCnkAnimateMotion(object_board_mh, p_motion, pwp->mj.nframe);
            }
        }
    }

    njSetMatrix(NULL, &mtx_BoardMH);

    njCnkSetMotionCallback(NULL);

    njCnkModDrawObject(object_o_board_mod);

    njPopMatrixEx();
}

void
ObjectBoardMHHook(TASK* tp)
{
    tp->twp->smode = tp->twp->ang.x & 1;
    tp->exec = (void*)0x006F7AF0;
    tp->dest = (void*)0x006FE430;
    tp->disp = (void*)0x006F7BE0;
    tp->disp_shad = ObjectBoardMHDisplayerMod;
}

void
CHS_BoardInit()
{
    KillCall(0x005EBC9B);
    WriteJump(0x005EBFC0, ObjectBoardCEDisplayerMod);
    WriteJump(0x006F7AC0, ObjectBoardMHHook);

    object_o_board_mod = RF_ChunkLoadObjectFile("o_board_mod");
}
