/*
Thread A
1 statement a1
2 statement a2

Thread B
1 statement b1
2 statement b2

we want to guarantee that a1 happens before b2 and b1 happens before a2.
*/

#include <iostream>
#include <thread>
#include <condition_variable>

using namespace std;

std::condition_variable cond;
std::mutex mu1, mu2;
bool a1happened = false, b1happened = false;

void function1() {
    std::unique_lock<std::mutex> locker1(mu1);
    cout<<"statement a1"<<endl;
    a1happened = true;
    cond.notify_one();
    cond.wait(locker1, [](){return b1happened;});
    cout<<"statement a2"<<endl;
}

void function2() {
    std::unique_lock<std::mutex> locker2(mu1);
    cout<<"statement b1"<<endl;
    b1happened = true;
    cond.notify_one();
    cond.wait(locker2, [](){return a1happened;});
    cout<<"statement b2"<<endl;
}

int main() {
    while(true)
    {
        std::thread t1(function1);
        std::thread t2(function2);
        t1.join();
        t2.join();
        cout<<"---------"<<endl;
        a1happened = false;
        b1happened = false;
    }
    return 0;
}