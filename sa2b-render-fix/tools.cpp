#include <sa2b/core.h>
#include <sa2b/user.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/texture.h>

void
SwapGVMTableIndex(int pGvmTable, int idx1, int idx2)
{
	TEX_GVMTABLE* gvmtable = (TEX_GVMTABLE*)pGvmTable;
	TEX_GVMTABLE tmp = gvmtable[idx1];
	gvmtable[idx1] = gvmtable[idx2];
	gvmtable[idx2] = tmp;
}

void
ModConflictWarning(const char* body)
{
	UserWarningMessageBox("Render Fix: Mod Conflict", body);
}