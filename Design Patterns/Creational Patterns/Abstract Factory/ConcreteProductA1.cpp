
/**
 * Concrete Products are created by corresponding Concrete Factories.
 */

#pragma once
#include "AbstractProductA.cpp"

class ConcreteProductA1 : public AbstractProductA {
public:
    std::string UsefulFunctionA() const override {
        return "Result of the Product A1";
    }
};