#include <iostream>
#include "Container.h"
#include "Data.h"

void ClientCode() {
    std::cout << "________________Iterator with int______________________________________" << std::endl;
    Container<int> cont;

    for(int i = 0; i < 10; i++) {
        cont.Add(i);
    }

    Iterator<int, Container<int> > *it = cont.CreaterIterator();
    for(it->First(); !it->IsDone(); it->Next()) {
        std::cout << *it->Current() << std::endl;
    }

    Container<Data> cont2;
    Data a(100), b(1000), c(10000);
    cont2.Add(a);
    cont2.Add(b);
    cont2.Add(c);

    std::cout << "________________Iterator with custom Class______________________________" << std::endl;
    Iterator<Data, Container<Data>> *it2 = cont2.CreaterIterator();
    for (it2->First(); !it2->IsDone(); it2->Next()) {
        std::cout << it2->Current()->data() << std::endl;
    }
    delete it;
    delete it2;
}

int main() {
    ClientCode();
    return 0;
}