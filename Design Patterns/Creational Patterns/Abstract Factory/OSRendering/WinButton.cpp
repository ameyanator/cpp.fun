#include "Button.cpp"

class WinButton : public Button {
public:
    void paint() const override {
        std::cout << "Win is Painting " << std::endl;
    }
};