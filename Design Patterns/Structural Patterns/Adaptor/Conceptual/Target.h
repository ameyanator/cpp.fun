#include <string>
#pragma once

class Target {
public:
    virtual ~Target() = default;
    virtual std::string Request() const {
        return "Target: The default target's behavior.\n";
    }
};