
#include "menu.h"
#include "components/ps3_gamepad.h"

GuiMenu* Menu;

int client = 0x136DF50;
int entity = 0x1235750;

void TakeWeapon(int ps, int weapon)
{
    if (hook::invoke<int>(0x3B5FB4, ps, weapon))
    {
        if (weapon - *(int*)(ps + 0x414) == 0)
        {
            if (*(int*)(ps + 0x424) & 2)
            {
                *(int*)(ps + 0x34) = 0;
                *(int*)(ps + 0x424) &= 0xFFFFFFFD;
                hook::invoke<void>(0x3AFEB4, ps, 1);
            }
        }
    }
}

void RefillAmmo(int ent, int weapon)
{
    hook::invoke<void>(0x21566C, ent, weapon, 0, 999, 1);

    if (hook::invoke<bool>(0x3B35F4, weapon))
    {
        hook::invoke<void>(0x21566C, ent, weapon, 1, 999, 1);
    }
}

void GiveWeapon(int ps, int ent, int weapon)
{
    if (hook::invoke<bool>(0x26A910, ps, weapon, 0, 0, 0))
    {
        //RefillAmmo(ent, weapon);
        hook::invoke<void>(0x217208, ent, weapon, 0);

    }
}

bool HasWeapon(int ps, int weapon)
{
    for (int i = 0; i < 15; i++)
    {
        if (*(int*)(ps + 0x2E8 + 4 * i) == weapon)
            return true;
    }
    return false;
}

void SwitchToWeapon(int ps, int weapon)
{
    if (!HasWeapon(ps, weapon))
        return;

    *(int*)(ps + 0x420) = 0;
    *(int*)(ps + 0x424) |= 0x200000;
    hook::invoke<void>(0x26B600, 0, weapon);
}

int GetCurrentWeapon(int ps)
{
    return *(int*)(ps + 0x420);
}

void GameMessage(const char* msg)
{
    hook::invoke<void>(0x3D0918, va("gm \"%s\"", msg));
}

void SelectWeapon(int& weapon)
{
    if (HasWeapon(client, weapon))
        return GameMessage("You already have this weapon");

    TakeWeapon(client, GetCurrentWeapon(client));
    GiveWeapon(client, entity, weapon);
    SwitchToWeapon(client, weapon);

    GameMessage(va("Weapon give: ^2%s", bg_weaponCompleteDefs[weapon]->szInternalName));
}

void TestCallback(int& i)
{
    printf("Option %i pressed!\n", i + 1);
}

void SetColor(vec3_t& color)
{
    Menu->Color = color;
}

GuiMenu::GuiMenu()
{
    CurrentMenu[0] = [](GuiMenu& menu)
    {
        menu.Title("Ghosts 1.16");
        menu.Submenu("Weapon menu", [](GuiMenu& menu)
            {
                menu.Title("Weapon menu");
                menu.Option("Dump bg_weaponCompleteDefs", []
                    {
                        printf("Dumping bg_weaponCompleteDefs...\n");
                        for (int i = 0; i < 240; i++)
                        {
                            if (!bg_weaponCompleteDefs[i] || !bg_weaponCompleteDefs[i]->szInternalName)
                                continue;

                            printf("[%i] '%s'\n", i, bg_weaponCompleteDefs[i]->szInternalName);
                        }
                    });
                menu.Submenu("Rifle menu", [](GuiMenu& menu)
                    {
                        menu.Title("Rifle menu");

                        for (int i = 2; i < 240; i++)
                        {
                            if (!bg_weaponCompleteDefs[i] || !bg_weaponCompleteDefs[i]->weapDef)
                                continue;

                            if (bg_weaponCompleteDefs[i]->weapDef->weapClass == WEAPCLASS_RIFLE)
                                menu.Option(bg_weaponCompleteDefs[i]->szInternalName, SelectWeapon, i);
                        }
                    });
                menu.Submenu("SMG menu", [](GuiMenu& menu)
                    {
                        menu.Title("SMG menu");

                        for (int i = 0; i < 240; i++)
                        {
                            if (!bg_weaponCompleteDefs[i] || !bg_weaponCompleteDefs[i]->weapDef)
                                continue;

                            if (bg_weaponCompleteDefs[i]->weapDef->weapClass == WEAPCLASS_SMG)
                                menu.Option(bg_weaponCompleteDefs[i]->szInternalName, SelectWeapon, i);
                        }
                    });
                menu.Submenu("Machine gun menu", [](GuiMenu& menu)
                    {
                        menu.Title("Machine gun menu");

                        for (int i = 0; i < 240; i++)
                        {
                            if (!bg_weaponCompleteDefs[i] || !bg_weaponCompleteDefs[i]->weapDef)
                                continue;

                            if (bg_weaponCompleteDefs[i]->weapDef->weapClass == WEAPCLASS_MG)
                                menu.Option(bg_weaponCompleteDefs[i]->szInternalName, SelectWeapon, i);
                        }
                    });
                menu.Submenu("Shotgun menu", [](GuiMenu& menu)
                    {
                        menu.Title("Shotgun menu");

                        for (int i = 0; i < 240; i++)
                        {
                            if (!bg_weaponCompleteDefs[i] || !bg_weaponCompleteDefs[i]->weapDef)
                                continue;

                            if (bg_weaponCompleteDefs[i]->weapDef->weapClass == WEAPCLASS_SPREAD)
                                menu.Option(bg_weaponCompleteDefs[i]->szInternalName, SelectWeapon, i);
                        }
                    });
                menu.Submenu("Sniper menu", [](GuiMenu& menu)
                    {
                        menu.Title("Sniper menu");

                        for (int i = 0; i < 240; i++)
                        {
                            if (!bg_weaponCompleteDefs[i] || !bg_weaponCompleteDefs[i]->weapDef)
                                continue;

                            if (bg_weaponCompleteDefs[i]->weapDef->weapClass == WEAPCLASS_SNIPER)
                                menu.Option(bg_weaponCompleteDefs[i]->szInternalName, SelectWeapon, i);
                        }
                    });
                menu.Submenu("Pistol menu", [](GuiMenu& menu)
                    {
                        menu.Title("Pistol menu");

                        for (int i = 0; i < 240; i++)
                        {
                            if (!bg_weaponCompleteDefs[i] || !bg_weaponCompleteDefs[i]->weapDef)
                                continue;

                            if (bg_weaponCompleteDefs[i]->weapDef->weapClass == WEAPCLASS_PISTOL)
                                menu.Option(bg_weaponCompleteDefs[i]->szInternalName, SelectWeapon, i);
                        }
                    });
                menu.Submenu("Rocket launcher menu", [](GuiMenu& menu)
                    {
                        menu.Title("Rocket launcher menu");

                        for (int i = 0; i < 240; i++)
                        {
                            if (!bg_weaponCompleteDefs[i] || !bg_weaponCompleteDefs[i]->weapDef)
                                continue;

                            if (bg_weaponCompleteDefs[i]->weapDef->weapClass == WEAPCLASS_ROCKETLAUNCHER)
                                menu.Option(bg_weaponCompleteDefs[i]->szInternalName, SelectWeapon, i);
                        }
                    });
            });
        menu.Submenu("Theme menu", [](GuiMenu& menu)
            {
                vec3_t red{ 1.0, 0.0, 0.0 };
                vec3_t green{ 0.0, 1.0, 0.0 };
                vec3_t blue{ 0.0, 0.0, 1.0 };
                vec3_t yellow{ 1.0, 1.0, 0.0 };
                vec3_t cyan{ 0.0, 1.0, 1.0 };
                vec3_t pink{ 1.0, 0.0, 1.0 };

                menu.Title("Theme menu");
                menu.Option("Color red", SetColor, red);
                menu.Option("Color green", SetColor, green);
                menu.Option("Color blue", SetColor, blue);
                menu.Option("Color yellow", SetColor, yellow);
                menu.Option("Color cyan", SetColor, cyan);
                menu.Option("Color pink", SetColor, pink);
            });
    };
}

void GuiMenu::Run()
{
    if (IsOpened())
    {
        TotalOptions = CurrentOptionDrawn;
        CurrentOptionDrawn = 0;

        vec2_t base = GetMenuPos();

        DrawRectFilled(Size.x, Size.y, base.x, base.y, {}, 0.75, GetMaterial("white"));

        CurrentMenu[SubmenuLevel](*this);

        if (SubmenuToEnter)
        {
            SubmenuChangeTime = Sys_Milliseconds();
            SavedOption[SubmenuLevel++] = CurrentOption;
            CurrentMenu[SubmenuLevel] = SubmenuToEnter;
            CurrentOption = 0;
            SubmenuToEnter = 0;
        }
    }

    for (int i = 0; i < 15; i++)
    {
        *(int*)(client + 0x440 + i * 8) = 999;
    }

    HandleInput();
}

void GuiMenu::HandleInput()
{
    if (!IsInputReady())
        return;

    if (!Opened)
    {
        if (IsButtonDown(BUTTON_L1) && IsButtonDown(BUTTON_R3))
            OnOpen();

        return;
    }

    if (IsButtonDown(BUTTON_CIRCLE))
        OnCancel();
    else if (IsButtonDown(BUTTON_DPAD_UP))
        OnScrollUp();
    else if (IsButtonDown(BUTTON_DPAD_DOWN))
        OnScrollDown();
}

bool GuiMenu::IsOpened()
{
    return Opened || !IsInputReady();
}

bool GuiMenu::IsInputReady()
{
    return Sys_Milliseconds() >= Tick;
}

void GuiMenu::InputSleep(int ms)
{
    Tick = Sys_Milliseconds() + ms;
}

void GuiMenu::OnOpen()
{
    Opened = true;
    OpenTime = Sys_Milliseconds();
    SubmenuChangeTime = Sys_Milliseconds();
    InputSleep(200);
}

void GuiMenu::OnClose()
{
    Opened = false;
    OpenTime = Sys_Milliseconds();
    InputSleep(200);
}

void GuiMenu::OnCancel()
{
    if (SubmenuLevel)
    {
        SubmenuChangeTime = Sys_Milliseconds();
        SubmenuLevel--;
        CurrentOption = SavedOption[SubmenuLevel];

        InputSleep(200);
    }
    else
    {
        OnClose();
    }
}

void GuiMenu::OnScrollUp()
{
    ScrollTime = Sys_Milliseconds();
    ScrollOption = CurrentOption;

    CurrentOption--;
    if (CurrentOption < 0)
        CurrentOption = TotalOptions - 1;

    InputSleep(ScrollDuration);
}

void GuiMenu::OnScrollDown()
{
    ScrollTime = Sys_Milliseconds();
    ScrollOption = CurrentOption;

    CurrentOption++;
    if (CurrentOption > TotalOptions - 1)
        CurrentOption = 0;

    InputSleep(ScrollDuration);
}

vec2_t GuiMenu::GetMenuPos()
{
    float from = Opened ? 1280.0 : Position.x;
    float to = Opened ? Position.x : 1280.0;

    return { Lerp<float>(from, to, CalculateTimeFraction(OpenTime, 200)), 0.0 };
}

vec2_t GuiMenu::GetCurrentOptionPos()
{
    vec2_t base = GetMenuPos();
    float fraction = CalculateTimeFraction(SubmenuChangeTime + 40 * CurrentOptionDrawn, 200);

    float x = Lerp<float>(1280.0 + Size.x * 0.5, base.x + Size.x * 0.5, fraction);
    float y = 150.0 + 25.0 * CurrentOptionDrawn;

    return { x, y };
}

vec3_t GuiMenu::GetCurrentOptionColor()
{
    float fraction = CalculateTimeFraction(ScrollTime, ScrollDuration);

    if (CurrentOptionDrawn == CurrentOption)
    {
        vec3_t color
        {
            Lerp<float>(TextColor[0], Color[0], fraction),
            Lerp<float>(TextColor[1], Color[1], fraction),
            Lerp<float>(TextColor[2], Color[2], fraction)
        };
        return color;
    }

    if (CurrentOptionDrawn == ScrollOption)
    {
        vec3_t color
        {
            Lerp<float>(Color[0], TextColor[0], fraction),
            Lerp<float>(Color[1], TextColor[1], fraction),
            Lerp<float>(Color[2], TextColor[2], fraction)
        };
        return color;
    }

    return TextColor;
}

float GuiMenu::GetCurrentOptionSize()
{
    float fraction = CalculateTimeFraction(ScrollTime, ScrollDuration);

    if (CurrentOptionDrawn == CurrentOption)
        return Lerp<float>(22.0, 25.0, fraction);

    if (CurrentOptionDrawn == ScrollOption)
        return Lerp<float>(25.0, 22.0, fraction);

    return 22.0;
}

void GuiMenu::Title(const char* text)
{
    DrawTextCenteredWithGlow(text, 30.0, GetMenuPos().x + Size.x * 0.5, 100.0, TextColor, 1.0, Color, 1.0, GetFont("fonts/objectiveFont"), 0);
}

void GuiMenu::Option(const char* text, void(*action)())
{
    vec2_t base = GetCurrentOptionPos();
    vec3_t color = GetCurrentOptionColor();
    float size = GetCurrentOptionSize();

    DrawCenteredText(text, size, base.x, base.y, color, 1.0, GetFont("fonts/objectiveFont"), 0);

    if (CurrentOptionDrawn == CurrentOption && IsInputReady() && IsButtonDown(BUTTON_CROSS))
    {
        if (action)
            action();

        InputSleep(200);
    }

    CurrentOptionDrawn++;
}

template<typename T>
void GuiMenu::Option(const char* text, void(*action)(T&), T& arg)
{
    vec2_t base = GetCurrentOptionPos();
    vec3_t color = GetCurrentOptionColor();
    float size = GetCurrentOptionSize();

    DrawCenteredText(text, size, base.x, base.y, color, 1.0, GetFont("fonts/objectiveFont"), 0);

    if (CurrentOptionDrawn == CurrentOption && IsInputReady() && IsButtonDown(BUTTON_CROSS))
    {
        if (action)
            action(arg);

        InputSleep(200);
    }

    CurrentOptionDrawn++;
}

void GuiMenu::Submenu(const char* text, void(*submenu)(GuiMenu&))
{
    vec2_t base = GetCurrentOptionPos();
    vec3_t color = GetCurrentOptionColor();
    float size = GetCurrentOptionSize();

    DrawCenteredText(text, size, base.x, base.y, color, 1.0, GetFont("fonts/objectiveFont"), 0);

    if (CurrentOptionDrawn == CurrentOption && IsInputReady() && IsButtonDown(BUTTON_CROSS))
    {
        SubmenuToEnter = submenu;

        InputSleep(200);
    }

    CurrentOptionDrawn++;
}