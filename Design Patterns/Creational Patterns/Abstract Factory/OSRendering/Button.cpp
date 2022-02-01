#include <iostream>
#pragma once

class Button {
public:
    virtual ~Button() {}
    virtual void paint() const = 0;
};