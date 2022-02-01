#include "Button.cpp"

class WinButton : public Button {
    void paint() override {
        std::cout << "Win is Painting " << std::endl;
    }
};