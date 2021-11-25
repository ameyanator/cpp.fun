#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

std::mutex mu, stdoutmu;
std::condition_variable cond;
int current_readers = 0;
bool writing;

using namespace std;

void Reader(int r) {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, [](){return !writing;});
    current_readers++;
    locker.unlock();

    std::unique_lock<std::mutex> locker2(stdoutmu);
    int time = rand() % 5;
    cout<<"Reader "<<r<<" is reading for "<<time<<"secs"<<endl;
    locker2.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(time));
    locker2.lock();
    cout<<"Reader "<<r<<" has finished reading"<<endl;
    locker2.unlock();

    locker.lock();
    current_readers--;
    locker.unlock();
    cond.notify_one();
}

void Writer(int w) {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, [](){return current_readers == 0 and !writing;});
    writing = true;
    int time = rand() % 5;
    cout<<"Writer "<<w<<" is writing for "<<time<<"secs"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(time));
    cout<<"Writer "<<w<<" has finished writing"<<endl;
    writing = false;
    locker.unlock();
    cond.notify_one();
}

int main() {
    vector<std::thread> threads;
    int n = 15;
    for(int i = 0; i < n; i++) {
        int x = rand();
        if(x % 3 == 0 or x % 3 == 1)
        {
            std::unique_lock<std::mutex> locker2(stdoutmu);
            cout<<i<<" is Reader"<<endl;
            locker2.unlock();
            threads.push_back(std::move(std::thread(Reader, i)));
        }
        else
        {
            std::unique_lock<std::mutex> locker2(stdoutmu);
            cout<<i<<" is Writer"<<endl;
            locker2.unlock();
            threads.push_back(std::move(std::thread(Writer, i)));
        }
    }
    for(int i = 0; i < threads.size(); i++)
        threads[i].join();
    return 0;
}
          

       
/*
  
*/