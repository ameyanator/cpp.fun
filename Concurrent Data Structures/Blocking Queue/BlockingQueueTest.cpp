#include <iostream>
#include "BlockingQueue.h"
#include <thread>
#include <future>

using namespace std;

BlockingQueue<int> bq;
std::mutex mu;

void add_to_queue(int x) {
    bq.push(x);
}

int pop_queue() {
    return bq.pop();
}

void push_into_queue() {
    // cout<<"push_into_queue"<<endl;
    int count = 0;
    while(true) {
        std::unique_lock<std::mutex> locker(mu);
        cout<<"Pushing into queue "<<++count<<endl;
        locker.unlock();
        add_to_queue(count);
        locker.lock();
        // cout<<"queue size "<<bq.size()<<endl;
        locker.unlock();
        std::this_thread::sleep_for (std::chrono::seconds(2));
    }
}

void pop_from_queue() {
    // cout<<"pop_from_queue"<<endl;
    while(true) {
        std::future<int> fu = std::async(pop_queue);
        int x = fu.get();
        std::unique_lock<std::mutex> locker(mu);
        std::cout<<"Got Value from queue "<<x<<std::endl;
        // cout<<"queue size "<<bq.size()<<endl;
        locker.unlock();
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }
}

void func() {
    std::cout<<"boo"<<std::endl;
}

int main() {
    
    // cout<<pop_from_queue()<<endl;
    std::thread t1(push_into_queue);
    std::thread t2(pop_from_queue);
    t1.join();
    t2.join();
}