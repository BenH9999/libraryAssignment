#include "raygui.h"
#include "Login.hpp"

Rectangle UserIDTextBoxRec;
int letterCount = 0;
int uID[16];
bool typing=0;

void runLogin(){
    bool finished = 0;
    
    while(!finished){
        if(WindowShouldClose()){
            CloseWindow();
        }
        drawLogin();
        processLogin();
    }
}

void processLogin(){
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    typing = 0;
    letterCount = 0;

    if(mouseX >= UserIDTextBoxRec.x && mouseY >= UserIDTextBoxRec.y && mouseX <= UserIDTextBoxRec.x+UserIDTextBoxRec.width && mouseY <= UserIDTextBoxRec.y+UserIDTextBoxRec.height){
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            typing = 1; 
        }else{
            typing = 0;
        }
    }else{
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    int key = GetCharPressed();

    while(key>0){
        if((key>=48) && (key<=57) && (letterCount < 16)){
            uID[letterCount] = (char)key;
            letterCount++;
        }
        key = GetCharPressed();
    }
    if(IsKeyPressed(KEY_BACKSPACE)){
        letterCount--;
        if(letterCount<0)letterCount=0;
        //uID[letterCount]
    }
}

void drawLogin(){
    BeginDrawing();

    ClearBackground(WHITE);

    DrawTextEx(mcFont,"Login!",{((float)(GetScreenWidth()/2)-80),20},70,0,BLACK);
    DrawTextEx(mcFont,"User ID:",{((float)(GetScreenWidth()/2)-80),150},30,0,BLACK);

    UserIDTextBoxRec  = {((float)(GetScreenWidth()/2)-80),190,200,30};

    DrawRectangleLinesEx(UserIDTextBoxRec,1,BLACK);

    for(int i = 0; i < letterCount; i++){
        
    }

    EndDrawing();
}