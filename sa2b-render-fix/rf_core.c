#include <samt/core.h>
#include <samt/msgbox.h>

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>

void
___DebugFuncError(const c8* func, const c8* body)
{
    c8 str[128];

    snprintf(str, sizeof(str), "Render Fix Debug: %s", func);

    mtMsgWarning(str, body);
}
