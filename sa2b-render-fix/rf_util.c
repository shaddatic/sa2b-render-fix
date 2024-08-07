#include <sa2b/core.h>
#include <sa2b/user.h>

/** Game **/
#include <sa2b/sonic/texture.h>

/** Render Fix **/
#include <rf_core.h>

/** Self **/
#include <rf_util.h>

void
RF_SwapTexFileTableIndex(TEX_PRSTABLE* pTexTable, int idx1, int idx2)
{
    TEX_PRSTABLE tmp = pTexTable[idx1];
    pTexTable[idx1] = pTexTable[idx2];
    pTexTable[idx2] = tmp;
}
