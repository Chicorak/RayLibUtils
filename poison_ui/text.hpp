#pragma once
#include "raylib.h"

/*
UiText Elements:
text(const char*)
textsize(int)
x, y(int)
selected(bool)
*/
struct UiText
{
    const char* text;
    int TextSize, x, y;
    bool selected = false;
};

//TODO: KeyBoard Control
//keys change a int value and array select 


bool uiTextHover (UiText Text)
{
    bool selected = false;
    if(CheckCollisionPointRec(GetMousePosition(), Rectangle{(float)Text.x, (float) Text.y, (int)TextLength(Text.text)*(float)Text.TextSize/1.5f, (float)Text.TextSize*2}))
        selected = true;
    return selected;
}
bool uiTextPressed (UiText Text)
{
    bool selected = false;
    if(CheckCollisionPointRec(GetMousePosition(), Rectangle{(float)Text.x, (float) Text.y, (int)TextLength(Text.text)*(float)Text.TextSize/1.5f, (float)Text.TextSize*2}) && IsMouseButtonPressed(0))
        selected = true;
    return selected;
}
bool uiTextHeld (UiText Text)
{
    bool selected = false;
    if(CheckCollisionPointRec(GetMousePosition(), Rectangle{(float)Text.x, (float) Text.y, (int)TextLength(Text.text)*(float)Text.TextSize/1.5f, (float)Text.TextSize*2}) && IsMouseButtonDown(0))
        selected = true;
    return selected;
}
void DrawUiText (UiText Text, Color color)
{
    DrawText(Text.text, Text.x, Text.y, Text.TextSize, color);
}
