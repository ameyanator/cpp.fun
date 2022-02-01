#include <iostream>
#pragma once

class Checkbox {
public:
    virtual void generate() const = 0;
    virtual ~Checkbox() {}
};