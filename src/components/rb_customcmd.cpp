
#include "game/game.h"
#include "utils/hooking.h"

// 0x48B92C - RB_DrawQuadPic

__attribute__((naked, noinline)) void RB_DrawQuadPic_Original(GfxCmdHeader* cmd)
{
    asm
    (
        ".set back_chain, -0x80;"
        ".set var_8, -8;"
        ".set arg_10,  0x10;"
        "stdu      %r1, back_chain(%r1);"
        "mflr      %r0;"
        "std       %r0, 0x80+arg_10(%r1);"
        "std       %r31, 0x80+var_8(%r1);"
        "lis       %r11, 0x48;"
        "ori       %r11, %r11, 0xB93C;"
        "mtctr     %r11;"
        "bctr;"
    );
}

void RB_DrawQuadPic_Hook(GfxCmdHeader* cmd)
{
    if(cmd->byteCount == sizeof(GfxCmdDrawQuadPic_Custom))
    {
        auto* custom = reinterpret_cast<GfxCmdDrawQuadPic_Custom*>(cmd);

        if (DB_MaterialStreamingFail(custom->material))
            return;

        RB_SetTessTechnique(custom->material, 2, 6);

        if (tess.vertexCount + 4 > 0x800 || tess.indexCount + 6 > 0xC00)
            RB_TessOverflow();

        tess.indices[tess.indexCount] = tess.vertexCount + 3;
        tess.indices[tess.indexCount + 1] = tess.vertexCount;
        tess.indices[tess.indexCount + 2] = tess.vertexCount + 2;
        tess.indices[tess.indexCount + 3] = tess.vertexCount + 2;
        tess.indices[tess.indexCount + 4] = tess.vertexCount;
        tess.indices[tess.indexCount + 5] = tess.vertexCount + 1;

        tess.verts[tess.vertexCount] = custom->verts[0];
        tess.verts[tess.vertexCount + 1] = custom->verts[1];
        tess.verts[tess.vertexCount + 2] = custom->verts[2];
        tess.verts[tess.vertexCount + 3] = custom->verts[3];

        tess.vertexCount += 4;
        tess.indexCount += 6;
    }
    else if(cmd->byteCount == sizeof(GfxCmdDrawQuadPic))
    {
        auto* original = reinterpret_cast<GfxCmdDrawQuadPic*>(cmd);

        if (DB_MaterialStreamingFail(original->material))
            return;

        RB_SetTessTechnique(original->material, 2, 6);

        if (tess.vertexCount + 4 > 0x800 || tess.indexCount + 6 > 0xC00)
            RB_TessOverflow();


        tess.indices[tess.indexCount] = tess.vertexCount + 3;
        tess.indices[tess.indexCount + 1] = tess.vertexCount;
        tess.indices[tess.indexCount + 2] = tess.vertexCount + 2;
        tess.indices[tess.indexCount + 3] = tess.vertexCount + 2;
        tess.indices[tess.indexCount + 4] = tess.vertexCount;
        tess.indices[tess.indexCount + 5] = tess.vertexCount + 1;

        float stTable[4][2]
        {
            { 0.0, 0.0 },
            { 1.0, 0.0 },
            { 1.0, 1.0 },
            { 0.0, 1.0 }
        };

        for (int i = 0; i < 4; i++)
        {
            R_SetVertex4D(&tess.verts[tess.vertexCount + i], original->verts[i][0], original->verts[i][1], 0.0, 1.0, stTable[i][0], stTable[i][1], original->color.packed);
        }

        tess.vertexCount += 4;
        tess.indexCount += 6;

        //RB_DrawQuadPic_Original(cmd);
    }
}

namespace rb_customcmd
{
    void start()
    {
        hook::jump(0x48B92C, *reinterpret_cast<uintptr_t*>(RB_DrawQuadPic_Hook));
    }

    void stop()
    {
        hook::copy(0x48B92C, *reinterpret_cast<uint32_t**>(RB_DrawQuadPic_Original), 4);
    }
}