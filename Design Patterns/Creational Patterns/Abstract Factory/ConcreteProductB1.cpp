/**
 * Concrete Products are created by corresponding Concrete Factories.
 */

#pragma once
#include <string>
#include "AbstractProductB.cpp"

class ConcreteProductB1 : public AbstractProductB {
public:
    std::string UsefulFunctionB() const override {
        return "Result of Product B1";
    }

    std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override{
        return "Result of Product B1 from another funtion ";
    }
};