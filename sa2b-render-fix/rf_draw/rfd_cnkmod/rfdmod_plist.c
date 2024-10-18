/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_mod.h>         /* modifier core                                        */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmod/rfdmod_internal.h> /* parent & siblings                */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
rjCnkModVolume(const Sint16* const pPList, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const Sint16* plist = pPList;

    const int count = plist[2];

    const int nb_vocnk = count & ~NJD_UFO_MASK;
    const int ufo      = count >> NJD_UFO_SHIFT;

    MOD_TRI* const p_modbuf = RFMOD_GetBuffer(nb_vocnk);

    if (!p_modbuf)
        return;

    plist = &plist[3];

    if ( RFMOD_GetInvertMode() )
    {
        for (s32 i = 0; i < nb_vocnk; ++i)
        {
            p_modbuf[i].vtx[2] = njvtxbuf[*plist++].pos;
            p_modbuf[i].vtx[1] = njvtxbuf[*plist++].pos;
            p_modbuf[i].vtx[0] = njvtxbuf[*plist++].pos;

            plist += ufo;
        }
    }
    else
    {
        for (s32 i = 0; i < nb_vocnk; ++i)
        {
            p_modbuf[i].vtx[0] = njvtxbuf[*plist++].pos;
            p_modbuf[i].vtx[1] = njvtxbuf[*plist++].pos;
            p_modbuf[i].vtx[2] = njvtxbuf[*plist++].pos;

            plist += ufo;
        }
    }
}

static void
rjCnkModStrip(const Sint16* const pPList, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const Sint16* plist = pPList;

    const int count = plist[2];

    const int nb_stcnk = count & ~NJD_UFO_MASK;
    const int ufo      = count >> NJD_UFO_SHIFT;

    CNK_STRIP* p_str = (void*)&plist[3];

    for (int i = 0; i < nb_stcnk; ++i)
    {
        const int nb_strip = ABS(p_str->len);

        const int nb_tri = (nb_strip - 2);

        bool invert = (p_str->len < 0);

        if (RFMOD_GetInvertMode())
            invert = !invert;

        /** nb_strip -> nb_tri **/
        MOD_TRI* p_modbuf = RFMOD_GetBuffer(nb_tri);

        for (int j = 0; j < nb_tri; ++j)
        {
            int idx[3];

            if (!invert)
            {
                idx[0] = p_str->d[j+0].i;
                idx[1] = p_str->d[j+1].i;
                idx[2] = p_str->d[j+2].i;
            }
            else
            {
                idx[2] = p_str->d[j+0].i;
                idx[1] = p_str->d[j+1].i;
                idx[0] = p_str->d[j+2].i;
            }

            p_modbuf->vtx[0] = njvtxbuf[idx[0]].pos;
            p_modbuf->vtx[1] = njvtxbuf[idx[1]].pos;
            p_modbuf->vtx[2] = njvtxbuf[idx[2]].pos;

            p_modbuf++;

            invert = !invert;
        }

        p_str = NEXT_STRIP(p_str, nb_strip, ufo);
    }
}

static void
rjCnkModStripUV(const Sint16* const pPList, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const Sint16* plist = pPList;

    const int count = plist[2];

    const int nb_stcnk = count & ~NJD_UFO_MASK;
    const int ufo      = count >> NJD_UFO_SHIFT;

    CNK_STRIP_UV* p_str = (void*)&plist[3];

    for (int i = 0; i < nb_stcnk; ++i)
    {
        const int nb_strip = ABS(p_str->len);

        const int nb_tri = (nb_strip - 2);

        bool invert = (p_str->len < 0);

        if (RFMOD_GetInvertMode())
            invert = !invert;

        /** nb_strip -> nb_tri **/
        MOD_TRI* p_modbuf = RFMOD_GetBuffer(nb_tri);

        for (int j = 0; j < nb_tri; ++j)
        {
            int idx[3];

            if (!invert)
            {
                idx[0] = p_str->d[j+0].i;
                idx[1] = p_str->d[j+1].i;
                idx[2] = p_str->d[j+2].i;
            }
            else
            {
                idx[2] = p_str->d[j+0].i;
                idx[1] = p_str->d[j+1].i;
                idx[0] = p_str->d[j+2].i;
            }

            p_modbuf->vtx[0] = njvtxbuf[idx[0]].pos;
            p_modbuf->vtx[1] = njvtxbuf[idx[1]].pos;
            p_modbuf->vtx[2] = njvtxbuf[idx[2]].pos;

            p_modbuf++;

            invert = !invert;
        }

        p_str = NEXT_STRIP(p_str, nb_strip, ufo);
    }
}

/****** Extern **********************************************************************/
void
rjCnkModPList(const Sint16* const pPList, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const Sint16* plist = pPList;
    int type;

    while (1)
    {
        type = ((u8*)plist)[0];

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        if (type == NJD_NULLOFF)
        {
            /** NJD_NULLOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_BITSOFF_MAX)
        {
            /** NJD_BITSOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type < NJD_MATOFF_MAX)
        {
            /** NJD_MATOFF **/

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type < NJD_VOLOFF_MAX)
        {
            /** NJD_VOLOFF **/

            switch ( VOSW(type) ) {
            case VOSW( NJD_CO_P3 ):

                rjCnkModVolume(plist, njvtxbuf);
                break;

            case VOSW( NJD_CO_P4 ):
            case VOSW( NJD_CO_ST ):
                break;
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type < NJD_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/
            switch ( STSW(type) ) {
            case STSW( NJD_CS ):

                rjCnkModStrip(plist, njvtxbuf);
                break;

            case STSW( NJD_CS_UVN ):
            case STSW( NJD_CS_UVH ):

                rjCnkModStripUV(plist, njvtxbuf);
                break;
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        /** An error occured, stop **/
        break;
    }
}
