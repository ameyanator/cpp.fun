#include "Button.cpp"

class MacButton : public Button {
    void paint() override {
        std::cout << "Mac is Painting " << std::endl;
    }
};