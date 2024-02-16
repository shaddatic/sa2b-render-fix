#include <sa2b/core.h>
#include <sa2b/user.h>

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>

void
___DebugFuncError(const utf8* func, const utf8* body)
{
    utf8 str[128];

    snprintf(str, sizeof(str), "Render Fix Debug: %s", func);

    UserWarningMessageBox(str, body);
}
