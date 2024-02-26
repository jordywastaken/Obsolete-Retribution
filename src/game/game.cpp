
#include "game.h"

float CalculateTimeFraction(int startTime, int duration)
{
    if (duration < 1)
        return 1.0;

    int deltaTime = Sys_Milliseconds() - startTime;

    if (deltaTime >= duration)
        return 1.0;

    if (deltaTime < 1)
        return 0.0;

    return static_cast<float>(deltaTime) / static_cast<float>(duration);
}

#define RoundUp(value, boundary) (value + (boundary - 1)) & -boundary
#define RoundDown(value, boundary) value & -boundary

GfxCmdHeader* R_GetCommandBuffer(int renderCmd, int bytes)
{
    if ((s_renderCmdBufferSize - s_cmdList->usedTotal) >= bytes)
    {
        auto* cmd = reinterpret_cast<GfxCmdHeader*>(&s_cmdList->cmds[s_cmdList->usedTotal]);
        cmd->id = renderCmd;
        cmd->byteCount = bytes;
        s_cmdList->lastCmd = cmd;
        s_cmdList->usedTotal = RoundUp(s_cmdList->usedTotal + bytes, 4);
        return cmd;
    }
    
    s_cmdList->lastCmd = 0;
    return 0;
}

void R_SetVertex4D(GfxVertex* vert, float x, float y, float z, float w, float s, float t, unsigned int color)
{
    vert->xyzw[0] = x;
    vert->xyzw[1] = y;
    vert->xyzw[2] = z;
    vert->xyzw[3] = w;
    vert->normal.packed = 2143289344;
    vert->color.packed = color;
    vert->texCoord[0] = s;
    vert->texCoord[1] = t;
}

void ScaleToResolution(float* x, float* y, float* width, float* height)
{
    struct
    {
        int width;
        int height;
        float aspectRatio;
    } screen;
    CL_GetScreenDimensions(&screen.width, &screen.height, &screen.aspectRatio);

    float xScale = static_cast<float>(screen.width) / 1280.0;
    float yScale = static_cast<float>(screen.height) / 720.0;

    if (x) *x *= xScale;
    if (y) *y *= yScale;
    if (width) *width *= xScale;
    if (height) *height *= yScale;
}

void DrawRectFilled(float width, float height, float x, float y, vec3_t color, float opacity, Material* material)
{
    float rgba[4]
    {
        color[0],
        color[1],
        color[2],
        opacity
    };

    ScaleToResolution(&x, &y, &width, &height);
    R_AddCmdDrawStretchPic(x, y, width, height, 0.0, 0.0, 1.0, 1.0, rgba, material);
}

void DrawRectGradient(float width, float height, float x, float y, vec3_t color[4], float opacity[4], Material* material)
{
    auto* cmd = reinterpret_cast<GfxCmdDrawQuadPic_Custom*>(R_GetCommandBuffer(14, sizeof(GfxCmdDrawQuadPic_Custom)));

    ScaleToResolution(&x, &y, &width, &height);

    float stTable[4][2]
    {
        { 0.0, 0.0 },
        { 1.0, 0.0 },
        { 1.0, 1.0 },
        { 0.0, 1.0 }
    };

    float xyTable[4][2]
    {
        { x, y },
        { x + width, y },
        { x + width, y + height },
        { x, y + height }
    };

    if (cmd)
    {
        cmd->material = material;

        for (int i = 0; i < 4; i++)
        {
            float vertColor[4]{ color[i][0], color[i][1], color[i][2], opacity[i] };

            R_SetVertex4D(&cmd->verts[i], xyTable[i][0], xyTable[i][1], 0.0, 1.0, stTable[i][0], stTable[i][1], 0);
            R_ConvertColorToBytes(vertColor, cmd->verts[i].color.array);
        }
    }
}

GfxCmdDrawText2D* DrawText(const char* text, float height, float x, float y, vec3_t color, float opacity, Font* font, int style)
{
    float rgba[4]
    {
        color[0],
        color[1],
        color[2],
        opacity
    };

    y += height;

    float xScale = height / static_cast<float>(R_TextHeight(font));
    float yScale = xScale;

    ScaleToResolution(&x, &y, &xScale, &yScale);
    return R_AddCmdDrawText(text, 0x7fffffff, font, x, y, xScale, yScale, 0.0, rgba, style);
}

GfxCmdDrawText2D* DrawCenteredText(const char* text, float height, float x, float y, vec3_t color, float opacity, Font* font, int style)
{
    x -= GetTextWidth(text, height, font) * 0.5;
    y -= height * 0.5;
    return DrawText(text, height, x, y, color, opacity, font, style);
}

void SetDrawText2DGlowParms(GfxCmdDrawText2D* cmd, vec3_t color, float opacity)
{
    cmd->renderFlags |= 0x30;

    float rgba[4]
    {
        color[0] * 0.1,
        color[1] * 0.1,
        color[2] * 0.1,
        opacity
    };
    R_ConvertColorToBytes(rgba, cmd->glowForceColor.array);
}

GfxCmdDrawText2D* DrawTextWithGlow(const char* text, float height, float x, float y, vec3_t color, float opacity, vec3_t glowColor, float glowOpacity, Font* font, int style)
{
    GfxCmdDrawText2D* cmd = DrawText(text, height, x, y, color, opacity, font, style);
    SetDrawText2DGlowParms(cmd, glowColor, opacity * glowOpacity);
}

GfxCmdDrawText2D* DrawTextCenteredWithGlow(const char* text, float height, float x, float y, vec3_t color, float opacity, vec3_t glowColor, float glowOpacity, Font* font, int style)
{
    GfxCmdDrawText2D* cmd = DrawCenteredText(text, height, x, y, color, opacity, font, style);
    SetDrawText2DGlowParms(cmd, glowColor, opacity * glowOpacity);
}

float GetTextWidth(const char* text, float height, Font* font)
{
    float xScale = height / static_cast<float>(R_TextHeight(font));
    return static_cast<float>(R_TextWidth(text, 0x7fffffff, font)) * xScale;
}

Material* GetMaterial(const char* name)
{
    Material* handle;
    LUI_Interface_RegisterMaterial(name, &handle);
    return handle;
}

Font* GetFont(const char* name)
{
    Font* handle;
    LUI_Interface_RegisterFont(name, &handle);
    return handle;
}