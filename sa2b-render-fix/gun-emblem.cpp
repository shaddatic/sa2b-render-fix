#include <sa2b/core.h>

#include <sa2b/ninja/ninja.h>

extern NJS_CNK_MODEL model_e_kumi_emblem[];
extern NJS_CNK_MODEL model_e_g_kumi_emblem[];
extern NJS_CNK_MODEL model_e_b_kumi_emblem[];
extern NJS_CNK_MODEL model_e_gold_emblem[];
extern NJS_CNK_MODEL model_e_kyoko_emblem[];

extern NJS_CNK_MODEL model_e_shouko_wing_port[];
extern NJS_CNK_MODEL model_e_shouko_wing_starboard[];
extern NJS_CNK_MODEL model_e_shouko_aft[];

extern NJS_CNK_MODEL model_e_g_pathkumi_emblem[];
extern NJS_CNK_MODEL model_e_b_pathkumi_emblem[];

extern NJS_CNK_MODEL model_e_t_emi_emblem[];
extern NJS_CNK_MODEL model_e_a_emi_emblem[];

#define ReplaceObjectModel(pobject, pmodel)		((NJS_CNK_OBJECT*)pobject)->model = pmodel

void 
GUNEmblemRestore()
{
	ReplaceObjectModel(0x014AB36C, model_e_kumi_emblem);
	ReplaceObjectModel(0x014ACF5C, model_e_g_kumi_emblem);
	ReplaceObjectModel(0x014AF6B4, model_e_b_kumi_emblem);

	ReplaceObjectModel(0x01492BA4, model_e_gold_emblem);

	ReplaceObjectModel(0x014CA69C, model_e_kyoko_emblem);

	ReplaceObjectModel(0x014CEA4C, model_e_shouko_wing_port);
	ReplaceObjectModel(0x014CE784, model_e_shouko_wing_starboard);
	ReplaceObjectModel(0x014CE4BC, model_e_shouko_aft);

	ReplaceObjectModel(0x01497AE4, model_e_g_pathkumi_emblem);
	ReplaceObjectModel(0x01495B8C, model_e_b_pathkumi_emblem);

	ReplaceObjectModel(0x014C9924, model_e_t_emi_emblem);
	ReplaceObjectModel(0x014C7744, model_e_a_emi_emblem);
}