/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_gene.h'
*
*   Contains functions related to Chao genes.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_GENE_H_
#define _SA2B_CHAO_GENE_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task             task;
typedef struct al_gene          AL_GENE;
typedef struct chao_param_gc    CHAO_PARAM_GC;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Fills gene struct with new gene data **/
void    AL_GeneCreate(AL_GENE* pGene);

/** Initial gene analysis **/
void    AL_GeneAnalyze(task* tp);

/** Internally called by 'AL_GeneAnalyze()' & 'AL_GeneAnalyze2()' **/
void    AL_GeneAnalyzeCommon(AL_GENE* pGene, CHAO_PARAM_GC* pParamGC);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_GeneCreate_p          ((void*)0x005506B0)
#   define AL_GeneAnalyzeCommon_p   ((void*)0x00551DA0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_GENE_H_*/
