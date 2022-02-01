#include "Checkbox.cpp"
#pragma once

class WinCheckbox : public Checkbox {
    void generate() override {
        std::cout << "Win is Generating " << std::endl;
    }
};