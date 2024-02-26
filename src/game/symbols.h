
#pragma once

namespace
{
    /***************************************************************
     * Functions
     **************************************************************/
    
    // libc
    static symbol<int(const char* fmt, ...)> printf{ 0x52449C };
    static symbol<const char* (const char* fmt, ...)> va{ 0x3690E8 };

    // universal
    static symbol<int()> Sys_Milliseconds{ 0x2C0110 };

    // database
    static symbol<void(XAssetHeader* header, XAssetType type, const char* name, int allowCreateDefault)> DB_FindXAssetHeader{ 0x17A4C8 };
    static symbol<bool(Material* material)> DB_MaterialStreamingFail{ 0x1814BC };

    // renderer
    static symbol<void(float* color, unsigned char* bytes)> R_ConvertColorToBytes{ 0x47EEF8 };
    static symbol<void()> R_EndFrame{ 0x465BD0 };
    static symbol<int(Font* font)> R_TextHeight{ 0x44AB50 };
    static symbol<int(const char* text, int maxChars, Font* font)> R_TextWidth{ 0x44AA08 };
    static symbol<void(int x, int y, int width, int height)> R_AddCmdSetViewportValues{ 0x465518 };
    static symbol<void(int x, int y, int width, int height)> R_AddCmdSetScissorRect{ 0x465590 };
    static symbol<void()> R_AddCmdClearScissorRect{ 0x465608 };
    static symbol<GfxCmdDrawText2D*(const char* text, int maxChars, Font* font, float x, float y, float xScale, float yScale, float rotation, const float* color, int style)> R_AddCmdDrawText{ 0x4649DC };
    static symbol<void(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float* color, Material* material)> R_AddCmdDrawStretchPic{ 0x4641FC };
    static symbol<void(float verts[4][2], const float* color, Material* material)> R_AddCmdDrawQuadPic{ 0x465250 };

    // renderer backend
    static symbol<void(Material* material, int techType, int primStatsTarget)> RB_SetTessTechnique{ 0x49C0A4 };
    static symbol<void()> RB_TessOverflow{ 0x49C1B0 };

    // client
    static symbol<void(int localClientNum, const char* cmd)> Cbuf_AddText{ 0x2DBB5C };
    static symbol<bool(int localClientNum)> CL_IsLocalClientInGame{ 0x13A6BC };
    static symbol<void(int* width, int* height, float* aspect)> CL_GetScreenDimensions{ 0x12C630 };

    // LUA
    static symbol<void(bool renderImmediately)> LUI_SetRenderImmediately{ 0x839C0 };
    static symbol<bool(const char* name, Material** handle)> LUI_Interface_RegisterMaterial{ 0x99EEC };
    static symbol<bool(const char* name, Font** handle)> LUI_Interface_RegisterFont{ 0x99F24 };

    // weapon
    static symbol<int(int weapon, bool isAlternate)> BG_GetWeaponType{ 0x3C3BD4 };
    static symbol<int(int weapon, bool isAlternate)> BG_GetWeaponClass{ 0x3B439C };

    /***************************************************************
     * Variables
     **************************************************************/

    // renderer
    static GfxCmdArray* (&s_cmdList) = *reinterpret_cast<GfxCmdArray**>(0x23F370C);
    static size_t& s_renderCmdBufferSize = *reinterpret_cast<size_t*>(0x220BC80);

    // renderer backend
    static GcmContext& g_gcmContext = *reinterpret_cast<GcmContext*>(0x26EE4CC);
    static materialCommands_t& tess = *reinterpret_cast<materialCommands_t*>(0x253CC30);
    static uintptr_t* RB_RenderCommandTable = reinterpret_cast<uintptr_t*>(0x62C444);

    // weapon
    static WeaponDef** bg_weaponDefs = reinterpret_cast<WeaponDef**>(0x1FBCB64);
    static WeaponCompleteDef** bg_weaponCompleteDefs = reinterpret_cast<WeaponCompleteDef**>(0x1FBC7AC);
}