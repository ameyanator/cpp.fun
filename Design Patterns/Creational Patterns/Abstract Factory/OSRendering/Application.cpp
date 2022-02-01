#include <iostream>
#include <string>

using namespace std;

#include "WinFactory.cpp"
#include "MacFactory.cpp"

void render(GUIFactory &factory) {
    Button *button = factory.createButton();
    Checkbox *checkbox = factory.createCheckbox();
    button->paint();
    delete button;
    delete checkbox;
}

int main() {
    string type;
    cout<<"Enter type"<<endl;
    cin>>type;
    if(type == "Win") {
        WinFactory* winfactory = new WinFactory();
        render(*winfactory);
    }
    else {
        // MacFactory* macfactory = new MacFactory();
        // render(*macfactory);
    }
}