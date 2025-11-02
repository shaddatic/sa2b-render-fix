#include <samt/core.h>
#include <samt/memory.h>
#include <samt/file.h>
#include <samt/writemem.h>
#include <samt/writeop.h>
#include <samt/model.h>

/** Util **/
#include <samt/util/endian.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_ninja.h>
#include <rf_eventinfo.h>

#define PTR_OFFSET      (0x7F210040)

#define FixPointer(p)   (*(uintptr_t*)p) -= PTR_OFFSET;

static bool
EV_IsByteswapped(const void* p)
{
    return ( (uintptr_t)(&EventData) <= (uintptr_t)(p) && (uintptr_t)(0x0241FE20) > (uintptr_t)(p) );
}

const int EventAnimateTexture_p = 0x006021A0;
static void
EventAnimateTexture(EVENT_TEXANIM_CHUNKDATA* a1, int a2, int a3)
{
    __asm
    {
        push[a3]
        mov edi, [a2]
        mov edx, [a1]
        call EventAnimateTexture_p
        add esp, 4
    }
}

const int EndiswapEventTexAnim1_p = 0x005FE8A0;
static void
EndiswapEventTexAnim1(EVENT_TEXANIM_CHUNKDATA* a1)
{
    __asm
    {
        mov eax, [a1]
        call EndiswapEventTexAnim1_p
    }
}

const int EndiswapEventTexAnim0_p = 0x005FE670;
static void
EndiswapEventTexAnim0(EVENT_TEXANIM_TEXIDS* a1)
{
    __asm
    {
        mov eax, [a1]
        call EndiswapEventTexAnim0_p
    }
}

static void
EventByteSwapTexAnim(EVENT_TEXANIM* p)
{
    EndianSwap(&p->nbTexId);

    EndianSwap(&p->pChunkData);

    if (p->pChunkData)
        *(int32_t*)&p->pChunkData -= PTR_OFFSET; // idky I'm doing this

    EndianSwap(&p->pTexIds);

    if (p->pTexIds)
        *(int32_t*)&p->pTexIds -= PTR_OFFSET;

    for (EVENT_TEXANIM_CHUNKDATA* ptexanim = p->pChunkData; ptexanim->count; ++ptexanim)
    {
        if (p->pChunkData)
            EndiswapEventTexAnim1(ptexanim);
    }

    for (int i = 0; i < p->nbTexId; ++i)
    {
        if (p->pTexIds)
            EndiswapEventTexAnim0(&p->pTexIds[i]);
    }
}

__declspec(naked)
static void
___EventByteSwapTexAnim(void)
{
    __asm
    {
        push ebx
        call EventByteSwapTexAnim
        pop ebx
        retn
    }
}

static void
EventByteSwapReflection(EVENT_REFLECTION* pReflect)
{
    EndianSwap(&pReflect->count);

    for (int i = 0; i < 32; ++i)
    {
        EndianSwap(&pReflect->AlphaValues[i]);
    }

    EndianSwap(&pReflect->ReflectionVtxs);

    if (pReflect->ReflectionVtxs)
    {
        FixPointer(&pReflect->ReflectionVtxs);

        const int nb = pReflect->count;

        for (int i = 0; i < nb; ++i)
        {
            NJS_POINT3* p_plane = &pReflect->ReflectionVtxs[i*4];

            EndianSwap(&p_plane[0].x);
            EndianSwap(&p_plane[0].y);
            EndianSwap(&p_plane[0].z);

            EndianSwap(&p_plane[1].x);
            EndianSwap(&p_plane[1].y);
            EndianSwap(&p_plane[1].z);

            EndianSwap(&p_plane[2].x);
            EndianSwap(&p_plane[2].y);
            EndianSwap(&p_plane[2].z);

            EndianSwap(&p_plane[3].x);
            EndianSwap(&p_plane[3].y);
            EndianSwap(&p_plane[3].z);
        }
    }
}

__declspec(naked)
static void
___EventByteSwapReflection(void)
{
    __asm
    {
        push eax
        call EventByteSwapReflection
        pop eax
        retn
    }
}

static void
EventByteSwapMainFile(EVENT_HEADER* pEvHead)
{
    if (pEvHead->nbScene & 0xFFFF0000) // is big-endian
    {
        EndianSwap(&pEvHead->pScenes);
        EndianSwap(&pEvHead->pTexlist);
        EndianSwap(&pEvHead->nbScene);
        EndianSwap(&pEvHead->pSpriteSizes);
        EndianSwap(&pEvHead->pReflections);
        EndianSwap(&pEvHead->pBlareObjects);
        EndianSwap(&pEvHead->pWalkerObjects);

        // Other stuff

        EndianSwap(&pEvHead->pMilesObjects);

        // Other stuff

        EndianSwap(&pEvHead->pEquipment);

        EndianSwap(&pEvHead->pTexAnims);
        EndianSwap(&pEvHead->dropShadow);

        // Other stuff

        if (pEvHead->pTexAnims)
        {
            EventByteSwapTexAnim(pEvHead->pTexAnims);
        }
    }
}

#define GET_PTR(p, offset)      (void*)((uintptr_t)(p) + (uintptr_t)(offset))

static void
EventFixTexlist(NJS_TEXLIST** pptls)
{
    OutputPointer(*pptls);

    const bool be = !( (u32)(*pptls) & 0x00007FFF );

    if ( be )
    {
        EndianSwap32( &(*pptls) );
    }

    OutputPointer(*pptls);

    NJS_TEXLIST* ptls = GET_PTR(*pptls, pptls);

    //const bool be = (bool)( ptls->nbTexture & 0xFFFF0000 );

    if ( be )
    {
        EndianSwap32( &ptls->textures );
        EndianSwap32( &ptls->nbTexture );
    }

    ptls->textures = GET_PTR(ptls->textures, pptls);

    NJS_TEXNAME* p_texn = ptls->textures;
    const u32   nb_texn = ptls->nbTexture;

    for ( u32 ix_texn = 0; ix_texn < nb_texn; ++ix_texn )
    {
        NJS_TEXNAME* p_curr_texn = &p_texn[ix_texn];

        if ( be )
        {
            EndianSwap32( &p_curr_texn->filename );
            EndianSwap32( &p_curr_texn->attr );
        }

        if ( p_curr_texn->filename )
        {
            p_curr_texn->filename = GET_PTR(p_curr_texn->filename, ptls);
        
            if ( p_curr_texn->attr )
            {
                NJS_TEXINFO* p_texinfo = p_curr_texn->filename;
        
                if ( be )
                {
                    EndianSwap32( &p_texinfo->texaddr );
                }
        
                p_texinfo->texaddr = GET_PTR(p_texinfo->texaddr, ptls);
            }
        }
    }
}

#define EventTexlist        DATA_REF(NJS_TEXLIST**, 0x01AEDE18)

static void
___EventByteSwapTexlist(void)
{
    EventFixTexlist(EventTexlist);
}

/****** Effect File *****************************************************************************/
void
EV_ByteswapEffectInfo(EV_EFF_INFO* pEffectInfo, bool bPartial)
{
    // subtitles
    {
        EV_EFF_SUBTITLE* p_subtitle = pEffectInfo->subtitle;

        for ( int i = 0; i < ARYLEN(pEffectInfo->subtitle); ++i )
        {
            EndianSwap32( &p_subtitle[i].frame );
            EndianSwap32( &p_subtitle[i].time );
        }
    }

    // sound
    {
        EV_EFF_SOUND* p_sound = pEffectInfo->sound;

        for ( int i = 0; i < ARYLEN(pEffectInfo->sound); ++i )
        {
            EndianSwap32( &p_sound[i].frame );
            // tone
            // staff
            EndianSwap16( &p_sound[i].voice_num );
            // bgm
            // jingle
            EndianSwap32( &p_sound[i].WaitVsyncCount );

            //EndianSwap32( &p_sound[i].padding[0] );
            //EndianSwap32( &p_sound[i].padding[1] );
            //EndianSwap32( &p_sound[i].padding[2] );
            //EndianSwap32( &p_sound[i].padding[3] );
            //EndianSwap32( &p_sound[i].padding[4] );
            //EndianSwap32( &p_sound[i].padding[5] );
            //EndianSwap32( &p_sound[i].padding[6] );
        }
    }

    // screen
    if ( !bPartial )
    {
        EV_EFF_SCREEN* p_screen = pEffectInfo->screen;

        for ( int i = 0; i < ARYLEN(pEffectInfo->screen); ++i )
        {
            EndianSwap32( &p_screen[i].frame );
            // type
            EndianSwap32( &p_screen[i].color );
            EndianSwap16( &p_screen[i].fadeout );
            EndianSwap16( &p_screen[i].texID );
            EndianSwap32( &p_screen[i].frametime );
            EndianSwap16( &p_screen[i].posX );
            EndianSwap16( &p_screen[i].posY );
            EndianSwap32( &p_screen[i].width );
            EndianSwap32( &p_screen[i].height );

            //EndianSwap32( &p_screen[i].padding[0] );
            //EndianSwap32( &p_screen[i].padding[1] );
            //EndianSwap32( &p_screen[i].padding[2] );
            //EndianSwap32( &p_screen[i].padding[3] );
            //EndianSwap32( &p_screen[i].padding[4] );
            //EndianSwap32( &p_screen[i].padding[5] );
            //EndianSwap32( &p_screen[i].padding[6] );
        }
    }

    // simpleptcl
    if ( !bPartial )
    {
        EV_EFF_SIMPLEPTCL* p_simpleptcl = pEffectInfo->simpleptcl;

        for ( int i = 0; i < ARYLEN(pEffectInfo->simpleptcl); ++i )
        {
            EndianSwap32( &p_simpleptcl[i].frame );
            // type
            // motionID
            EndianSwap32( &p_simpleptcl[i].texID );
            EndianSwap32( &p_simpleptcl[i].pulsectrl );
            EndianSwap32( &p_simpleptcl[i].unkF );
            EndianSwap32( &p_simpleptcl[i].scl );

            //EndianSwap32( &p_simpleptcl[i].padding[0] );
            //EndianSwap32( &p_simpleptcl[i].padding[1] );
            //EndianSwap32( &p_simpleptcl[i].padding[2] );
            //EndianSwap32( &p_simpleptcl[i].padding[3] );
            //EndianSwap32( &p_simpleptcl[i].padding[4] );
            //EndianSwap32( &p_simpleptcl[i].padding[5] );
            //EndianSwap32( &p_simpleptcl[i].padding[6] );
        }
    }

    // lights
    if ( !bPartial )
    {
        EV_EFF_LIGHT* p_light = pEffectInfo->lights[0];

        for ( int i = 0; i < (4*256); ++i )
        {
            EndianSwap32( &p_light[i].frame );
            EndianSwap32( &p_light[i].fademode );
            EndianSwap32( &p_light[i].vec.x );
            EndianSwap32( &p_light[i].vec.y );
            EndianSwap32( &p_light[i].vec.z );
            EndianSwap32( &p_light[i].r );
            EndianSwap32( &p_light[i].g );
            EndianSwap32( &p_light[i].b );
            EndianSwap32( &p_light[i].ambi_inten );
            EndianSwap32( &p_light[i].ambi_r );
            EndianSwap32( &p_light[i].ambi_g );
            EndianSwap32( &p_light[i].ambi_b );

            //EndianSwap32( &p_light[i].padding[0] );
            //EndianSwap32( &p_light[i].padding[1] );
            //EndianSwap32( &p_light[i].padding[2] );
            //EndianSwap32( &p_light[i].padding[3] );
            //EndianSwap32( &p_light[i].padding[4] );
        }
    }

    // blares
    if ( !bPartial )
    {
        EV_EFF_BLARE* p_blare = pEffectInfo->blares;

        for ( int i = 0; i < ARYLEN(pEffectInfo->blares); ++i )
        {
            EndianSwap32( &p_blare[i].frame );
            EndianSwap32( &p_blare[i].duration );
            // param1
            // param2
            // param3
            // param4
            // param5
            // param6
            EndianSwap32( &p_blare[i].lifetime );

            //EndianSwap32( &p_blare[i].padding[ 0] );
            //EndianSwap32( &p_blare[i].padding[ 1] );
            //EndianSwap32( &p_blare[i].padding[ 2] );
            //EndianSwap32( &p_blare[i].padding[ 3] );
            //EndianSwap32( &p_blare[i].padding[ 4] );
            //EndianSwap32( &p_blare[i].padding[ 5] );
            //EndianSwap32( &p_blare[i].padding[ 6] );
            //EndianSwap32( &p_blare[i].padding[ 7] );
            //EndianSwap32( &p_blare[i].padding[ 8] );
            //EndianSwap32( &p_blare[i].padding[ 9] );
            //EndianSwap32( &p_blare[i].padding[10] );
        }
    }

    // ptcls
    if ( !bPartial )
    {
        EV_EFF_PTCL* p_ptcl = pEffectInfo->ptcls;
    
        for ( int i = 0; i < ARYLEN(pEffectInfo->ptcls); ++i )
        {
            EndianSwap32( &p_ptcl[i].pos.x );
            EndianSwap32( &p_ptcl[i].pos.y );
            EndianSwap32( &p_ptcl[i].pos.z );
            EndianSwap32( &p_ptcl[i].vec.x );
            EndianSwap32( &p_ptcl[i].vec.y );
            EndianSwap32( &p_ptcl[i].vec.z );
            EndianSwap16( &p_ptcl[i].unk16_0 );
            EndianSwap16( &p_ptcl[i].unk16_1 );
            EndianSwap16( &p_ptcl[i].unk16_2 );
            EndianSwap16( &p_ptcl[i].unk16_3 );
            EndianSwap32( &p_ptcl[i].frame );
            EndianSwap32( &p_ptcl[i].spread.x );
            EndianSwap32( &p_ptcl[i].spread.y );
            EndianSwap32( &p_ptcl[i].spread.z );
            EndianSwap32( &p_ptcl[i].count );
            EndianSwap32( &p_ptcl[i].unk32_0 );
            EndianSwap32( &p_ptcl[i].type );
            EndianSwap32( &p_ptcl[i].unk32_1 );
        }
    }

    // movie overlays
    if ( !bPartial )
    {
        EV_EFF_OVERLAY* p_overlay = pEffectInfo->overlays;

        for ( int i = 0; i < ARYLEN(pEffectInfo->overlays); ++i )
        {
            EndianSwap32( &p_overlay[i].frame );
            EndianSwap16( &p_overlay[i].posX );
            EndianSwap16( &p_overlay[i].posY );
            EndianSwap32( &p_overlay[i].depth );
            // type
            EndianSwap16( &p_overlay[i].texID );
            // fname

            //EndianSwap32( &p_overlay[i].padding[0] );
            //EndianSwap32( &p_overlay[i].padding[1] );
            //EndianSwap32( &p_overlay[i].padding[2] );
            //EndianSwap32( &p_overlay[i].padding[3] );
        }
    }
}

static void
ByteswapEffectInfo(EV_EFF_INFO* pEffectInfo)
{
    EV_ByteswapEffectInfo(pEffectInfo, false);
}

/****** Init ************************************************************************************/
void
EV_ByteSwapInit(void)
{
    WriteCall(0x005FEFF7, ___EventByteSwapTexAnim);
    WriteJump(0x005FE320, ___EventByteSwapReflection);

    WriteJump(0x00603040, EV_ByteswapEffectInfo);

    //WriteJump(0x00600120, ___EventByteSwapTexlist);
}
