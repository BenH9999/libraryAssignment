#include "raygui.h"
#include "handleScreens.hpp"

User currentUser;
Library l;

Font mcFont;
Font mcFont100px;
Rectangle loginButtonBounds;
bool hoverLogin = false;
int drawOffsetX = 0;
int drawOffsetY = 0;

void runScreens(){
    screenType s = MAINMENU;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(850,460,"Library System");

    mcFont = LoadFont("font/minecraft.ttf");

    GuiSetFont(GetFontDefault());

    SetTargetFPS(60);

    while(!WindowShouldClose()){
        drawScreens(s);
        processScreens(s);
    }
    CloseWindow();
}

void drawScreens(screenType s){
    BeginDrawing();

    switch(s){
        case MAINMENU:{
            drawMainMenu();
        }
        case LIBRARY:{

        }
    }

    EndDrawing();
}

void drawMainMenu(){
    ClearBackground(backgroundColour);

    DrawTextEx(mcFont,"Library",{((float)(GetScreenWidth()/2)-120),(20)},70,0,black);

    loginButtonBounds = {((float)(GetScreenWidth()/2)-80),150,150,60};

    DrawRectangleLinesEx(loginButtonBounds,2,black);
    
    if(hoverLogin){
        DrawRectangleRec(loginButtonBounds,hoverC);
    }

    DrawTextEx(mcFont,"Login",{loginButtonBounds.x+10,loginButtonBounds.y+10},50,0,black);
}

void processScreens(screenType s){
    switch(s){
        case MAINMENU:{
            processMainMenu();
        }
        case LIBRARY:{

        }
    }
}

void processMainMenu(){
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    //login button
    if(mouseX >= loginButtonBounds.x && mouseY >= loginButtonBounds.y && mouseX <= loginButtonBounds.x+loginButtonBounds.width && mouseY <= loginButtonBounds.y+loginButtonBounds.height){
        hoverLogin = 1;
    }else{
        hoverLogin = 0;
    }

    if(hoverLogin && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        runLogin();
    }
}

void initMenuBounds(){

}