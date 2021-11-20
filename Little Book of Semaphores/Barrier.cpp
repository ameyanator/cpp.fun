/*
1 rendezvous
2 critical point

22 Basic synchronization patterns
The synchronization requirement is that no thread executes critical point
until after all threads have executed rendezvous.
*/

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>

using namespace std;

int n, threads_executed;
std::mutex mu;
std::condition_variable cond;

void function(int x) {
    std::unique_lock<std::mutex> locker(mu);
    cout<<"rendezvous "<<x<<endl;
    threads_executed++;
    cond.notify_all();

    cond.wait(locker, [](){return threads_executed == n;});
    cout<<"critical section "<<x<<endl;
}

int main() {
    n = 10;
    vector<std::thread> threads(n);
    for(int i = 0; i < n; i++) {
        threads[i] = std::move(std::thread(function, i));
    }
    for(int i = 0; i < n; i++) {
        threads[i].join();
    }
    return 0;
}