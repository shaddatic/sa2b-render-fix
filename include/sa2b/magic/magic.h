/*
*   Sonic Adventure Mod Tools (SA2B) - '/magic/magic.h'
*
*   Description:
*       Magic is the render API used by SoC. It was used to
*   make development easier, as Magic supported a range of
*   devices/consoles.
*
*   Contributors:
*   -   Magic Developers
*   -   kellnc
*   -   MainMemory
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _MAGIC_H_
#define _MAGIC_H_

#ifdef  __cplusplus

/************************/
/*  Base                */
/************************/
namespace Magic::Base
{
    template <typename T>
    class Singleton
    {
    private:
        static T* const m_pSubject;
    public:
        T* GetSubject()
        {
            if (!m_pSubject)
            {
                m_pSubject = new T();
            }
            return m_pSubject;
        }
    };
}

/************************/
/*  Magic               */
/************************/
#include <sa2b/magic/input.h>
#include <sa2b/magic/math.h>
#include <sa2b/magic/rendercore.h>

#endif/*__cplusplus*/

#endif/*_MAGIC_H_*/
