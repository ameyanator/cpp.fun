/*
imagine that threads represent ballroom dancers and that two
kinds of dancers, leaders and followers, wait in two queues before entering the
dance floor. When a leader arrives, it checks to see if there is a follower waiting.
If so, they can both proceed. Otherwise it waits.
Similarly, when a follower arrives, it checks for a leader and either proceeds
or waits, accordingly.
*/

#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

queue<int> leaders, followers;
std::mutex mu,mu2;
std::condition_variable cond;

void check_if_possible() {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, [](){return (!leaders.empty() and !followers.empty()) or (leaders.empty() and followers.empty());});
    if(leaders.empty() and followers.empty())
        return;
    cout<<"Leader "<<leaders.front()<<" walks with follower "<<followers.front()<<endl;
    leaders.pop();
    followers.pop();
}

void Leader(int l) {
    std::unique_lock<std::mutex> locker(mu);
    std::cout<<"Leader "<<l<<" arrives "<<std::endl;
    leaders.push(l);
    locker.unlock();
    std::this_thread::sleep_for (std::chrono::seconds(3));
    check_if_possible();
    std::this_thread::sleep_for (std::chrono::seconds(2));
    cond.notify_one();
    // cout<<"Leader exit"<<endl;
}

void Follower(int l) {
    std::unique_lock<std::mutex> locker(mu);
    std::cout<<"Follower "<<l<<" arrives "<<std::endl;
    followers.push(l);
    locker.unlock();
    std::this_thread::sleep_for (std::chrono::seconds(2));
    check_if_possible();
    std::this_thread::sleep_for (std::chrono::seconds(3));
    cond.notify_one();
    // cout<<"Follower exit"<<endl;
}

int main() {
    int n = 5;
    vector<std::thread> threads(2*n);
    for(int i = 0; i < n; i++) {
        // cout<<"index "<<i<<" and index "<<n+i<<endl;
        threads[i] = std::move(std::thread(Leader, i));
        threads[n+i] = std::move(std::thread(Follower, n+i));
    }
    for(int i = 0; i < 2*n; i++)
    {
        // cout<<"i "<<i<<endl;
        threads[i].join();
    }
    return 0;
}

/*
0 1 4 3 2
5 9 8 7 6
*/