#include <iostream>
#include "BlockingQueue.h"
#include <thread>
#include <future>

BlockingQueue<int> bq;

void add_to_queue(int x) {
    bq.push(x);
}

int pop_from_queue() {
    return bq.pop();
}

void func() {
    std::cout<<"boo"<<std::endl;
}

int main() {
    std::thread t1(add_to_queue, 1);
    // cout<<pop_from_queue()<<endl;
    std::future<int> fu = std::async(pop_from_queue);
    std::cout<<fu.get()<<std::endl;
}