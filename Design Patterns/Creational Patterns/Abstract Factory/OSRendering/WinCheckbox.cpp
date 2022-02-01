#include "Checkbox.cpp"
#pragma once

class WinCheckbox : public Checkbox {
    void generate() const override {
        std::cout << "Win is Generating " << std::endl;
    }
};