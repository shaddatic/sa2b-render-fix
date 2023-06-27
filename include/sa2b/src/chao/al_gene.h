#pragma once

struct task;
struct AL_GENE;
struct CHAO_PARAM_GC;

void AL_GeneCreate (AL_GENE* pGene);

void AL_GeneAnalyzeCommon(AL_GENE* pGene, CHAO_PARAM_GC* pParamGC);

void AL_GeneAnalyze(task* tp);