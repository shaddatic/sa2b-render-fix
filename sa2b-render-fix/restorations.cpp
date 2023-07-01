#include <sa2b/core.h>
#include <sa2b/config.h>
#include <sa2b/memtools.h>
#include <sa2b/model.h>
#include <sa2b/mods.h>

#include <sa2b/ninja/ninja.h>

#include <tint-disable.h>
#include <tools.h>

#include <enemy-jet.h>

#define ReplaceObjectModel(pobject, pmodel)		((NJS_CNK_OBJECT*)pobject)->model = pmodel

static void
GUNEmblemRestore()
{
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

	/*  */

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

static void
JungleObjectTreeRestore()
{
	extern NJS_TEXLIST texlist_jo_tree[];

	GJS_OBJECT* object_jo_tree = LoadGinjaObject2(GetModPath(), "model/jo_tree.sa2bmdl");

	WriteData(0x00EA3134, *object_jo_tree->model,	GJS_MODEL);
	WriteData(0x00EA2D60, *texlist_jo_tree,			NJS_TEXLIST);
}

#define SECT "rest"

void
RestorationSettings(const config* conf)
{
	if (ConfigGetInt(conf, SECT, "emblem", 1))
	{
		if (CheckForMod("RestoredGUNLogos"))
		{
			ModConflictWarning(
				"The 'Restored GUN Logos' mod will conflict with Render Fix's 'GUN Emblem Fix' setting!\n\n"
				"Please disable either the 'Restored GUN Logos' mod, or the 'GUN Emblem Fix' setting!"
			);
		}

		GUNEmblemRestore();
	}

	if (ConfigGetInt(conf, SECT, "jet", 1))
	{
		EnemyJetDisplayerFix();
	}

	if (ConfigGetInt(conf, SECT, "jo_tree", 1))
	{
		JungleObjectTreeRestore();
	}

	if (ConfigGetInt(conf, SECT, "dc_ring", 0))
	{
		DisableTintGinjaModel((GJS_MODEL*)0x00B58288);
	}
}