/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_emotion.h'
*
*   Contains enums related to Chao emotions.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_EMOTION_H_
#define _SA2B_CHAO_EMOTION_H_

/************************/
/*  Enums               */
/************************/
enum
{
    EM_MD_PLEASURE = 0x0,
    EM_MD_ANGER = 0x1,
    EM_MD_SORROW = 0x2,
    EM_MD_FEAR = 0x3,
    EM_MD_SURPRISE = 0x4,
    EM_MD_PAIN = 0x5,
    EM_MD_RELAX = 0x6,
    EM_MD_TOTAL = 0x7,
    EM_ST_SLEEPY = 0x8,
    EM_ST_SLEEP_DEPTH = 0x9,
    EM_ST_HUNGER = 0xA,
    EM_ST_BREED = 0xB,
    EM_ST_TEDIOUS = 0xC,
    EM_ST_LONELY = 0xD,
    EM_ST_TIRE = 0xE,
    EM_ST_STRESS = 0xF,
    EM_ST_NOURISHMENT = 0x10,
    EM_ST_CONDITION = 0x11,
    EM_ST_THIRSTY = 0x12,
    EM_PER_CURIOSITY = 0x13,    // Normal / Curious
    EM_PER_KINDNESS = 0x14,     // Kindness
    EM_PER_AGRESSIVE = 0x15,    // Crybaby / Energetic
    EM_PER_SLEEPY_HEAD = 0x16,  // Niave / Normal
    EM_PER_SOLITUDE = 0x17,     // Solitude
    EM_PER_VITALITY = 0x18,     // Vitality
    EM_PER_GLUTTON = 0x19,      // Normal / Big Eater
    EM_PER_REGAIN = 0x1A,       // Regain
    EM_PER_SKILLFUL = 0x1B,     // Skillful
    EM_PER_CHARM = 0x1C,        // Charm
    EM_PER_CHATTY = 0x1D,       // Chatty
    EM_PER_CALM = 0x1E,         // Normal / Carefree
    EM_PER_FICKLE = 0x1F,       // Fickle
    NB_EMOTION = 0x20,
};

#endif /* _SA2B_CHAO_EMOTION_H_ */
