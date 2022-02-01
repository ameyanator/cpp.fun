#include <iostream>
#include "ConcreteFactory1.cpp"
#include "AbstractProductA.cpp"
#include "ConcreteFactory2.cpp"
#include "AbstractProductB.cpp"

void ClientCode(AbstractFactory &f) {
    const AbstractProductA *product_a = f.CreateProductA();
    const AbstractProductB *product_b = f.CreateProductB();
    std::cout << product_a->UsefulFunctionA() << std::endl;
    std::cout << product_b->UsefulFunctionB() << std::endl;
    delete product_a;
    delete product_b;
}

int main() {
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1 *f1 = new ConcreteFactory1();
    ClientCode(*f1);
    std::cout << "Client: Testing client code with the second factory type:\n";
    ConcreteFactory2 *f2 = new ConcreteFactory2();
    ClientCode(*f2);
}