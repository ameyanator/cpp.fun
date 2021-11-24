#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

using namespace std;

queue<int> buffer;
std::mutex mu;
std::condition_variable cond;

void Producer() {
    int item = 0;
    while(true) {
        std::this_thread::sleep_for (std::chrono::seconds(3));
        std::unique_lock<std::mutex> locker(mu);
        item++;
        cout<<"Produced item "<<item<<" into queue"<<endl;
        buffer.push(item);
        cond.notify_one();
    }
}

void Consumer() {
    while(true) {
        std::this_thread::sleep_for (std::chrono::seconds(2));
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){return !buffer.empty();});
        int item = buffer.front();
        buffer.pop();
        cout<<"Consumed item "<<item<<" from queue"<<endl;
    }
}

int main() {
    std::thread t1(Producer);
    std::thread t2(Consumer);
    t1.join(); t2.join();
    return 0;
}

/*

    7 8 9 10
*/