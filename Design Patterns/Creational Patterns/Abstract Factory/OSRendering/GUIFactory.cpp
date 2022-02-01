#include "Button.cpp"
#include "Checkbox.cpp"
#include "MacButton.cpp"
#include "WinButton.cpp"
#include "MacCheckbox.cpp"
#include "WinCheckbox.cpp"
#pragma once

class GUIFactory {
public:
    virtual Button* createButton() const = 0;
    virtual Checkbox* createCheckbox() const = 0;
};