/**
 * Each distinct product of a product family should have a base interface. All
 * variants of the product must implement this interface.
 */

#pragma once
#include <string>
#include "AbstractProductA.cpp"

class AbstractProductB {
public:
    virtual ~AbstractProductB() {}
    virtual std::string UsefulFunctionB() const = 0;

/**
   * ...but it also can collaborate with the ProductA.
   *
   * The Abstract Factory makes sure that all products it creates are of the
   * same variant and thus, compatible.
*/
    virtual std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const = 0;
};