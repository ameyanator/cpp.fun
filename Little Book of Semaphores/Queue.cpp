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
std::mutex mu;
std::condition_variable cond;

void Leader(int l) {
    std::unique_lock<std::mutex> locker(mu);
    std::cout<<"Leader "<<l<<" arrives "<<std::endl;
    leaders.push(l);
    cond.notify_all();

    cond.wait(locker, [](){return !leaders.empty() and !followers.empty();});
    cout<<"Leader "<<leaders.front()<<" walks with follower "<<followers.front()<<endl;
    leaders.pop();
    followers.pop();
}

void Follower(int l) {
    std::unique_lock<std::mutex> locker(mu);
    std::cout<<"Follower "<<l<<" arrives "<<std::endl;
    followers.push(l);
    cond.notify_all();

    cond.wait(locker, [](){return !leaders.empty() and !followers.empty();});
    cout<<"Leader "<<leaders.front()<<" walks with follower "<<followers.front()<<endl;
    leaders.pop();
    followers.pop();
}

int main() {
    vector<std::thread> threads(20);
    for(int i = 0; i < 10; i++) {
        cout<<"index "<<i<<endl;
        threads[i] = std::move(std::thread(Leader, i));
        threads[2*i+1] = std::move(std::thread(Follower, 2*i+1));
    }
    for(int i = 0; i < 20; i++)
    {
        cout<<"i "<<i<<endl;
        threads[i].join();
    }
    return 0;
}