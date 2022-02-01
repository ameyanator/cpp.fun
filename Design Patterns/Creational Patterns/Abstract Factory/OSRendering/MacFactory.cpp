#include "GUIFactory.cpp"

class MacFactory : public GUIFactory {
    Button* createButton()const override {
        return new MacButton();
    }

    Checkbox* createCheckbox()const override {
        return new MacCheckbox();
    }
};