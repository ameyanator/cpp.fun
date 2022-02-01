#include "Button.cpp"

class MacButton : public Button {
public:
    void paint() const override {
        std::cout << "Mac is Painting " << std::endl;
    }
};