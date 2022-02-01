/**
 * Concrete Products are created by corresponding Concrete Factories.
 */

#pragma once
#include <string>
#include "AbstractProductB.cpp"

class ConcreteProductB2 : public AbstractProductB {
public:
    std::string UsefulFunctionB() const override {
        return "Result of Product B2";
    }

    std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override{
        return "Result of Product B2 from another funtion ";
    }
};