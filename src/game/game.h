
#pragma once

#include <sys/sys_types.h>

#include "enums.h"
#include "structs.h"

#include "utils/hooking.h"

#pragma diag_suppress 1070
template<typename T>
class symbol
{
public:
    constexpr symbol(uintptr_t obj)
        : sp_object_(obj)
    { }

    operator T* ()
    {
        volatile uintptr_t object_fptr[]{ this->sp_object_, hook::toc() };

        T* type = *reinterpret_cast<T*>(this->sp_object_);
        return (decltype(type))object_fptr;
    }

    T* get()
    {
        return this->sp_object_;
    }

    uintptr_t sp_object_;
};

float CalculateTimeFraction(int startTime, int duration);

template<typename T>
static T Lerp(T from, T to, float fraction)
{
    return from + (to - from) * fraction;
}

template<typename T>
static T Clamp(T value, T min, T max)
{
    return value < min ? min : value > max ? max : value;
}

template<typename T>
static T Min(T a, T b)
{
    return a < b ? a : b;
}

template<typename T>
static T Max(T a, T b)
{
    return a > b ? a : b;
}

GfxCmdHeader* R_GetCommandBuffer(int renderCmd, int bytes);
void R_SetVertex4D(GfxVertex* vert, float x, float y, float z, float w, float s, float t, unsigned int color);

void DrawRectFilled(float width, float height, float x, float y, vec3_t color, float opacity, Material* material);
void DrawRectGradient(float width, float height, float x, float y, vec3_t color[4], float opacity[4], Material* material);
GfxCmdDrawText2D* DrawText(const char* text, float height, float x, float y, vec3_t color, float opacity, Font* font, int style);
GfxCmdDrawText2D* DrawCenteredText(const char* text, float height, float x, float y, vec3_t color, float opacity, Font* font, int style);
void SetDrawText2DGlowParms(GfxCmdDrawText2D* cmd, vec3_t color, float opacity);
GfxCmdDrawText2D* DrawTextWithGlow(const char* text, float height, float x, float y, vec3_t color, float opacity, vec3_t glowColor, float glowOpacity, Font* font, int style);
GfxCmdDrawText2D* DrawTextCenteredWithGlow(const char* text, float height, float x, float y, vec3_t color, float opacity, vec3_t glowColor, float glowOpacity, Font* font, int style);
float GetTextWidth(const char* text, float height, Font* font);
Material* GetMaterial(const char* name);
Font* GetFont(const char* name);

#include "symbols.h"

#ifdef _DEBUG
#define debug_print printf
#else
#define debug_print(fmt, ...)
#endif