#pragma once

#include "Library.hpp"
#include "raylib.h"
#include "Login.hpp"

#define backgroundColour GetColor(0xffffffff)
#define hoverC GetColor(0x9cb9ffff)
#define black GetColor(0x000000ff)

typedef enum screenType{
    MAINMENU,
    LIBRARY,
}screenType;

void runScreens();
void processScreens(screenType s);
void processMainMenu();
void drawScreens(screenType s);
void drawMainMenu();
void initMenuBounds();

extern User currentUser;
extern Library l;
extern Font mcFont;