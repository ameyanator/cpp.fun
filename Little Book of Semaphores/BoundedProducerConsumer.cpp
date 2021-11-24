#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

using namespace std;

queue<int> buffer;
std::mutex mu;
std::condition_variable cond;
int buffer_limit;

void Producer() {
    int item = 0;
    while(true) {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){return buffer.size() < buffer_limit;});
        item++;
        cout<<"Produced item "<<item<<" into queue"<<endl;
        buffer.push(item);
        locker.unlock();
        cond.notify_one();
        std::this_thread::sleep_for (std::chrono::seconds(2));
    }
}

void Consumer() {
    while(true) {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){return !buffer.empty();});
        int item = buffer.front();
        buffer.pop();
        cout<<"Consumed item "<<item<<" from queue"<<endl;
        locker.unlock();
        cond.notify_one();
        std::this_thread::sleep_for (std::chrono::seconds(4));
    }
}

int main() {
    buffer_limit = 5;
    std::thread t1(Producer);
    std::thread t2(Consumer);
    t1.join(); t2.join();
    return 0;
}

/*
        10 11 12 13
*/