
#pragma once

enum XAssetType
{
	ASSET_TYPE_PHYSPRESET,
	ASSET_TYPE_PHYS_COLLMAP,
	ASSET_TYPE_XANIM,
	ASSET_TYPE_XMODELSURFS,
	ASSET_TYPE_XMODEL,
	ASSET_TYPE_MATERIAL,
	ASSET_TYPE_VERTEXSHADER,
	ASSET_TYPE_PIXELSHADER,
	ASSET_TYPE_TECHSET,
	ASSET_TYPE_IMAGE,
	ASSET_TYPE_SOUND,
	ASSET_TYPE_SNDCURVE,
	ASSET_TYPE_LPFCURVE,
	ASSET_TYPE_REVERBSENDCURVE,
	ASSET_TYPE_LOADED_SOUND,
	ASSET_TYPE_COL_MAP_SP,
	ASSET_TYPE_COM_MAP,
	ASSET_TYPE_GLASS_MAP,
	ASSET_TYPE_AIPATHS,
	ASSET_TYPE_VEHICLE_TRACK,
	ASSET_TYPE_MAP_ENTS,
	ASSET_TYPE_FX_MAP,
	ASSET_TYPE_GFX_MAP,
	ASSET_TYPE_LIGHTDEF,
	ASSET_TYPE_UI_MAP,
	ASSET_TYPE_FONT,
	ASSET_TYPE_MENUFILE,
	ASSET_TYPE_MENU,
	ASSET_TYPE_ANIMCLASS,
	ASSET_TYPE_LOCALIZE,
	ASSET_TYPE_ATTACHMENT,
	ASSET_TYPE_WEAPON,
	ASSET_TYPE_SNDDRIVERGLOBALS,
	ASSET_TYPE_FX,
	ASSET_TYPE_IMPACTFX,
	ASSET_TYPE_SURFACEFX,
	ASSET_TYPE_AITYPE,
	ASSET_TYPE_MPTYPE,
	ASSET_TYPE_CHARACTER,
	ASSET_TYPE_XMODELALIAS,
	ASSET_TYPE_RAWFILE,
	ASSET_TYPE_SCRIPTFILE,
	ASSET_TYPE_STRINGTABLE,
	ASSET_TYPE_LEADERBOARDDEF,
	ASSET_TYPE_STRUCTUREDDATADEF,
	ASSET_TYPE_TRACER,
	ASSET_TYPE_VEHICLE,
	ASSET_TYPE_ADDON_MAP_ENTS,
	ASSET_TYPE_NETCONSTSTRINGS,
	ASSET_TYPE_REVERBPRESET,
	ASSET_TYPE_LUAFILE,
	ASSET_TYPE_SCRIPTABLE,
	ASSET_TYPE_EQUIPSNDTABLE,
	ASSET_TYPE_DOPPLERPRESET
};

enum MaterialVertexDeclType
{ 
	VERTDECL_GENERIC, 
	VERTDECL_PACKED, 
	VERTDECL_QUANTIZED, 
	VERTDECL_QUANTIZED_NOCOLOR, 
	VERTDECL_QUANTIZED_SKINNED_CACHED_MODEL, 
	VERTDECL_QUANTIZED_SKINNED_CACHED_NOCOLOR_MODEL, 
	VERTDECL_QUANTIZED_SKINNED_MODEL, 
	VERTDECL_QUANTIZED_SKINNED_NOCOLOR_MODEL, 
	VERTDECL_WORLD, 
	VERTDECL_WORLD_T1N0,
	VERTDECL_WORLD_T1N1, 
	VERTDECL_WORLD_T2N0, 
	VERTDECL_WORLD_T2N1, 
	VERTDECL_WORLD_T2N2, 
	VERTDECL_WORLD_T3N0,
	VERTDECL_WORLD_T3N1, 
	VERTDECL_WORLD_T3N2,
	VERTDECL_WORLD_T4N0, 
	VERTDECL_WORLD_T4N1, 
	VERTDECL_WORLD_T4N2, 
	VERTDECL_POS_TEX, 
	VERTDECL_COUNT
};

enum LUIAlignment
{
	LUI_ALIGNMENT_NONE = 0,
	LUI_ALIGNMENT_LEFT = (1 << 0),
	LUI_ALIGNMENT_CENTER = (1 << 1),
	LUI_ALIGNMENT_RIGHT = (1 << 2),
	LUI_ALIGNMENT_TOP = (1 << 3),
	LUI_ALIGNMENT_MIDDLE = (1 << 4),
	LUI_ALIGNMENT_BOTTOM = (1 << 5),
	LUI_ALIGNMENT_SCREEN_SPACE = (1 << 6),

	LUI_ALIGNMENT_HORIZONTAL_MASK = (LUI_ALIGNMENT_LEFT | LUI_ALIGNMENT_CENTER | LUI_ALIGNMENT_RIGHT),
	LUI_ALIGNMENT_VERTICAL_MASK = (LUI_ALIGNMENT_TOP | LUI_ALIGNMENT_MIDDLE | LUI_ALIGNMENT_BOTTOM)
};

enum weapClass_t
{ 
	WEAPCLASS_RIFLE, 
	WEAPCLASS_SNIPER,
	WEAPCLASS_MG, 
	WEAPCLASS_SMG, 
	WEAPCLASS_SPREAD, 
	WEAPCLASS_PISTOL, 
	WEAPCLASS_GRENADE, 
	WEAPCLASS_ROCKETLAUNCHER, 
	WEAPCLASS_TURRET,
	WEAPCLASS_THROWINGKNIFE,
	WEAPCLASS_NON_PLAYER, 
	WEAPCLASS_ITEM, 
	WEAPCLASS_NUM
};