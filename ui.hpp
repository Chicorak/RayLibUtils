#pragma once 
#include "poison_ui/buttons.hpp"
#include "poison_ui/text.hpp"
/* Buttons Defines */

//Returns true if it has been pressed
bool CheckButtonPress(Button button);

//Returns true if it has being held
bool CheckButtonHeld(Button button);

//Returns true if it has Realeased
bool CheckButtonReleased(Button button);

//Returns true if the mouse selected is up
bool CheckButtonUp(Button button);

//End of  Button defines -----------------------

/*Selectable Text Defines */
bool uiTextHover (UiText Text);
bool uiTextPressed (UiText Text);
bool uiTextHeld (UiText Text);
/* Takes UiText type and raylib color type*/
void DrawUiText (UiText Text, Color color);
/*
Ui Elements:

Selectable text: O
        Buttons: X
        Sliders: O
*/
