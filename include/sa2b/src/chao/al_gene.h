/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_gene.h'
*
*   Contains functions related to Chao genes.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_GENE_H_
#define _SA2B_CHAO_GENE_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task             TASK;
typedef struct al_gene          AL_GENE;
typedef struct chao_param_gc    CHAO_PARAM_GC;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Fills gene struct with new gene data **/
void    AL_GeneCreate(AL_GENE* pGene);

/** Initial gene analysis **/
void    AL_GeneAnalyze(TASK* tp);

/** Internally called by 'AL_GeneAnalyze()' & 'AL_GeneAnalyze2()' **/
void    AL_GeneAnalyzeCommon(AL_GENE* pGene, CHAO_PARAM_GC* pParamGC);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
EXTERN const void* const AL_GeneCreate_p;
EXTERN const void* const AL_GeneAnalyzeCommon_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_GENE_H_ */
