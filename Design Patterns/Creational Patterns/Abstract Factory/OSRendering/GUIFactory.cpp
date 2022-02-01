#include "Button.cpp"
#include "Checkbox.cpp"
#include "MacButton.cpp"
#include "WinButton.cpp"
#include "MacCheckbox.cpp"
#include "WinCheckbox.cpp"
#pragma once

class GUIFactory {
    Button* createButton() ;
    Checkbox* createCheckbox();
};