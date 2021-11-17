#include <mutex>
#include <condition_variable>
#include <deque>
#include <climits>
#include <iostream>

using namespace std;

template<typename T>
class BlockingQueue {
private:
    std::mutex _mu;
    std::condition_variable _cn_signal;
    std::deque<T> _dq;
    int capacity;
public:
    BlockingQueue() {
        capacity = INT_MAX;
    }

    BlockingQueue(int capacity) {
        this->capacity = capacity;
    }

    void push(T const &value) {
        {
            std::unique_lock<std::mutex> locker(_mu);
            if(_dq.size() == capacity)
                _cn_signal.wait(locker, [this](){return _dq.size() < capacity;});
            _dq.push_back(value);
        }
        cout<<"notifying from push"<<endl;
        _cn_signal.notify_one();
    }

    T pop() {
        {
            std::unique_lock<std::mutex> locker(_mu);
            if(_dq.empty())
                _cn_signal.wait(locker, [this](){ return !_dq.empty();});
            T val = _dq.front(); _dq.pop_front();
            _cn_signal.notify_one();
            return val;
        }
    }

    int size() {
        {
            std::lock_guard<std::mutex> locker(_mu);
            return _dq.size();
        }
    }
};