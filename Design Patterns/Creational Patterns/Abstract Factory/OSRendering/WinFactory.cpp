#include "GUIFactory.cpp"

class WinFactory : public GUIFactory {
    Button* createButton() {
        return new WinButton();
    }
    Checkbox* createCheckbox() {
        return new WinCheckbox();
    }
};