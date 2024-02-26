
#pragma once

#undef vector
struct vec2_t
{
    union
    {
        struct { float x, y; };
        float v[2];
    };

    vec2_t() : x(0), y(0) { }
    vec2_t(float value) : x(value), y(value) { }
    vec2_t(float* value) : x(value[0]), y(value[1]) { }
    vec2_t(float x, float y) : x(x), y(y) { }

    float& operator[](const int i)
    {
        return v[i];
    }
};

struct vec3_t
{
    union
    {
        struct { float x, y, z; };
        struct { float pitch, yaw, roll; };
        float v[3];
    };

    vec3_t() : x(0), y(0), z(0) { }
    vec3_t(float value) : x(value), y(value), z(value) { }
    vec3_t(float* value) : x(value[0]), y(value[1]), z(value[2]) { }
    vec3_t(float x, float y, float z) : x(x), y(y), z(z) { }

    float& operator[](const int i)
    {
        return v[i];
    }
};

struct vec4_t
{
    union
    {
        struct { float x, y, z, w; };
        struct { float r, g, b, a; };
        float v[4];
    };

    vec4_t() : x(0), y(0), z(0), w(0) { }
    vec4_t(float value) : x(value), y(value), z(value), w(value) { }
    vec4_t(float* value) : x(value[0]), y(value[1]), z(value[2]), w(value[3]) { }
    vec4_t(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }

    float& operator[](const int i)
    {
        return v[i];
    }
};

//
// Polygon mode:
// - 0x1B00 Point
// - 0x1B01 Wireframe
// - 0x1B02 Filled
//
struct GcmContext
{
    int* begin;
    int* end;
    int* current;
    int(*callbackForSnc)(GcmContext* ctx, int count);
};

struct Font
{
    const char* name; 
    int pixelHeight;
    // ...
};

struct MaterialInfo
{
    const char* name;
    // ...
};

struct Material
{
    MaterialInfo info;
    // ...
};

union XAssetHeader
{
    Material* material;
    Font* font;
};

struct LUIAnimationState
{
    Material* material;
    Font* font;
    // ...

};

struct LUIElement
{
    LUIAnimationState currentAnimationState;
    // ...
};

union GfxColor
{ 
    unsigned char array[4]; 
    unsigned int packed; 
};

union PackedUnitVec
{
    unsigned int packed;
};

struct GfxVertex
{ 
    float xyzw[4]; 
    GfxColor color; 
    float texCoord[2]; 
    PackedUnitVec normal; 
};

struct materialCommands_t
{ 
    GfxVertex verts[2048]; 
    unsigned short indices[3072]; 
    MaterialVertexDeclType vertDeclType; 
    unsigned int vertexSize; 
    unsigned int indexCount; 
    unsigned int vertexCount; 
    unsigned int firstVertex; 
    unsigned int lastVertex; 
};

struct GfxCmdHeader
{
    unsigned short id; 
    unsigned short byteCount;
};

struct GfxCmdDrawText2D
{ 
    GfxCmdHeader header; 
    float x; 
    float y; 
    float rotation; 
    Font* font; 
    float xScale; 
    float yScale; 
    GfxColor color; 
    int maxChars; 
    int renderFlags; 
    int cursorPos;
    char cursorLetter;
    GfxColor glowForceColor;
    int fxBirthTime;
    int fxLetterTime;
    int fxDecayStartTime;
    int fxDecayDuration;
    Material* fxMaterial; 
    Material* fxMaterialGlow;
    float padding; 
    char text[3]; 
};

struct GfxCmdDrawQuadPic
{ 
    GfxCmdHeader header; 
    Material* material; 
    float verts[4][2]; 
    GfxColor color; 
};

struct GfxCmdDrawQuadPic_Custom
{
    GfxCmdHeader header;
    Material* material;
    GfxVertex verts[4];
};

struct GfxCmdArray
{ 
    unsigned char* cmds; 
    int usedTotal; 
    int usedCritical; 
    GfxCmdHeader* lastCmd; 
};

struct WeaponDef
{
    char __padding_0x0[0x4C];
    int weapType; // 0x4C
    int weapClass; // 0x50
};

struct WeaponCompleteDef
{
    const char* szInternalName;
    WeaponDef* weapDef;
};

struct Ammo
{
    int amount;
    int weapon;
};

struct playerState_s
{
    int serverTime; // 0x0
    char __padding_0x4[0x2E4];
    int weaponsEquipped[15]; // 0x2E8
    char __padding_0x324[0x440 - 0x324];
    Ammo ammoNotInClip[15]; // 0x440
};

struct gclient_s
{
    playerState_s ps;
};

struct gentity_s
{
    gclient_s* client; // 0x10C
};