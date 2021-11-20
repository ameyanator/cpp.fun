/*
1 rendezvous
2 critical point

22 Basic synchronization patterns
The synchronization requirement is that no thread executes critical point
until after all threads have executed rendezvous.

Often a set of cooperating threads will perform a series of steps in a loop and
synchronize at a barrier after each step. For this application we need a reusable
barrier that locks itself after all the threads have passed through.
*/

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>

using namespace std;

int n, threads_executed = 0, critical_section_executed = 0;
std::mutex mu;
std::condition_variable cond;
bool all_threads_executed = false;

void function(int x) {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, [](){return threads_executed < n and critical_section_executed < n;});
    cout<<"rendezvous "<<x<<endl;
    threads_executed++;
    cond.notify_all();

    cond.wait(locker, [](){return threads_executed == n;});
    cout<<"critical section "<<x<<endl;
    critical_section_executed++;
}

int main() {
    n = 10;
    vector<std::thread> threads(2*n);
    for(int i = 0; i < 2*n; i++) {
        threads[i] = std::move(std::thread(function, i));
    }
    for(int i = 0; i < 2*n; i++) {
        threads[i].join();
    }
    return 0;
}