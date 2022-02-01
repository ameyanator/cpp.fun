#include "GUIFactory.cpp"

class WinFactory : public GUIFactory {
public:
    Button* createButton() const override {
        return new WinButton();
    }
    Checkbox* createCheckbox() const override {
        return new WinCheckbox();
    }
};