
#pragma once

#include "game/game.h"

class GuiMenu
{
public:
    GuiMenu();

    void Run();
    void HandleInput();

    bool IsOpened();
    bool IsInputReady();
    void InputSleep(int ms);

    void OnOpen();
    void OnClose();
    void OnCancel();
    void OnScrollUp();
    void OnScrollDown();

    vec2_t GetMenuPos();
    vec2_t GetCurrentOptionPos();
    vec3_t GetCurrentOptionColor();
    float GetCurrentOptionSize();

    void Title(const char* text);
    void Option(const char* text, void(*action)() = 0);
    template<typename T>
    void Option(const char* text, void(*action)(T&), T& arg);
    void Submenu(const char* text, void(*submenu)(GuiMenu&) = 0);


    bool Opened{};
    int Tick{};
    int CurrentOption{};
    int CurrentOptionDrawn{};
    int TotalOptions{};

    int SubmenuLevel{};
    void(*CurrentMenu[5])(GuiMenu&) {};
    int SavedOption[5]{};
    void(*SubmenuToEnter)(GuiMenu&) {};

    int OpenTime{};
    int SubmenuChangeTime{};
    int ScrollTime{};
    int ScrollOption{};
    int ScrollDuration{ 160 };

    vec2_t Position{ 880.0, 0.0 };
    vec2_t Size{ 300.0, 720.0 };
    vec3_t Color{ 1.0, 0.0, 0.0 };
    vec3_t TextColor{ 1.0, 1.0, 1.0 };
};

extern GuiMenu* Menu;