#include "Checkbox.cpp"
#pragma once

class MacCheckbox : public Checkbox {
    void generate() const override {
        std::cout << "Mac is Generating " << std::endl;
    }
};