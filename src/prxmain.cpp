
#include <sys/moduleexport.h>

#include "globals.h"
#include "game/game.h"
#include "components/ps3_gamepad.h"
#include "components/rb_customcmd.h"
#include "components/scheduler.h"
#include "gui/menu.h"
#include "utils/hooking.h"
#include "utils/file.h"
#include "utils/imports.h"

///
/// Module exports
/// 
#pragma diag_suppress 77
SYS_MODULE_INFO(iw6-mod, 0, 1, 0);
SYS_MODULE_START(_Z16RetributionStartv);
SYS_MODULE_STOP(_Z15RetributionStopv);

int RetributionStart()
{
    debug_print("[Retribution]: Started\n");

    Menu = new GuiMenu();

    // utils
    hook::start(init_proc, 20);

    // components
    scheduler::start();
    rb_customcmd::start();
    ps3_gamepad::start();

    scheduler::add(scheduler::renderer, []
        {
            if(CL_IsLocalClientInGame(0))
                Menu->Run();
        });

    return 0;
}

int RetributionStop()
{
    debug_print("[Retribution]: Stopped\n");

    // utils 
    hook::stop();

    // components
    scheduler::stop();
    rb_customcmd::stop();

    delete Menu;

    return 0;
}