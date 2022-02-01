
/**
 * Concrete Factories produce a family of products that belong to a single
 * variant. The factory guarantees that resulting products are compatible. Note
 * that signatures of the Concrete Factory's methods return an abstract product,
 * while inside the method a concrete product is instantiated.
 */

#pragma once
#include "AbstractFactory.cpp"
#include "ConcreteProductA1.cpp"
#include "ConcreteProductB1.cpp"

class ConcreteFactory1 : public AbstractFactory {
    AbstractProductA* CreateProductA() const override {
        return new ConcreteProductA1();
    }

    AbstractProductB* CreateProductB() const override {
        return new ConcreteProductB1();
    }
};