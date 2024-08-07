/*
*   Sonic Adventure Mod Tools (SA2B) - '/magic/base.h'
*
*   Description:
*       Magic's Base namespace.
*
*   Contributors:
*     - Magic Developers
*     - kellnc
*     - MainMemory
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_MAGIC_BASE
#define H_MAGIC_BASE

#ifdef  __cplusplus

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

#endif/*__cplusplus*/

#endif/*H_MAGIC_BASE*/
