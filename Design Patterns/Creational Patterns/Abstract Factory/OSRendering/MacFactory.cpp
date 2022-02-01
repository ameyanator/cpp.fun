#include "GUIFactory.cpp"

class MacFactory : public GUIFactory {
    Button* createButton() {
        return new MacButton();
    }

    Checkbox* createCheckbox() {
        return new MacCheckbox();
    }
};