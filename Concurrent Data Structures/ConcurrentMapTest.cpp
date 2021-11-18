#include <iostream>
#include "ConcurrentMap.h"
#include <string>
#include <thread>
#include <future>

using namespace std;

ConcurrentMap<int, string> cmap;
std::mutex mu;

void add_to_map(int x, string s) {
    cmap.insert(x, s);
}

size_t remove_from_map(int x) {
    return cmap.erase(x);
}

string get_value_from_map(int x) {
    return cmap.at(x);
}

void insert_into_map() {
    // cout<<"push_into_queue"<<endl;
    int count = 0;
    string s = "a";
    while(true) {
        std::unique_lock<std::mutex> locker(mu);
        cout<<"Pushing into queue "<<++count<<"->"<<s+s<<endl;
        locker.unlock();
        s += s;
        add_to_map(count, s);
        locker.lock();
        cout<<"map size "<<cmap.size()<<endl;
        locker.unlock();
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }
}

void remove_from_map_caller() {
    // cout<<"pop_from_queue"<<endl;
    int count = 0;
    while(true) {
        std::unique_lock<std::mutex> locker(mu);
        cout<<"removing from map"<<endl;
        size_t retval = remove_from_map(++count);
        std::cout<<"Removed Key from map "<<count<<" value "<<retval<<std::endl;
        cout<<"map size "<<cmap.size()<<endl;
        locker.unlock();
        std::this_thread::sleep_for (std::chrono::seconds(3));
    }
}

void get_value_from_map_caller() {
    int count = 0;
    while(true) {
        std::unique_lock<std::mutex> locker(mu);
        cout<<"calling get from key "<<++count<<endl;
        std::future<string> fu = std::async(std::launch::async, [&](){return get_value_from_map(count);});
        locker.unlock();
        string s = fu.get();
        locker.lock();
        std::cout<<"Got Value from map key "<<count<<" value "<<s<<std::endl;
        cout<<"map size "<<cmap.size()<<endl;
        locker.unlock();
        std::this_thread::sleep_for (std::chrono::seconds(2));
    }
}

int main() {
    std::thread t1(insert_into_map);
    std::thread t2(remove_from_map_caller);
    std::thread t3(get_value_from_map_caller);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}