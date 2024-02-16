#include <sa2b/core.h>
#include <sa2b/user.h>

/** Source **/
#include <sa2b/src/texture.h>

/** Render Fix **/
#include <rf_core.h>

/** Self **/
#include <rf_util.h>

void
RF_SwapTexFileTableIndex(TEX_FILETABLE* pTexTable, int idx1, int idx2)
{
    TEX_FILETABLE tmp = pTexTable[idx1];
    pTexTable[idx1] = pTexTable[idx2];
    pTexTable[idx2] = tmp;
}
