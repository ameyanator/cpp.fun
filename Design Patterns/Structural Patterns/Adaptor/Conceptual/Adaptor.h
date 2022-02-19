#include "Target.h"
#include "Adaptee.h"
#include <algorithm>
#pragma once

class Adaptor : public Target {
private:
    Adaptee *adaptee_;
public:
    Adaptor(Adaptee *adaptee): adaptee_(adaptee) {}

    std::string Request() const override {
        std::string to_reverse = this->adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) \n" + to_reverse;
    }
};