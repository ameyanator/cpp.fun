#include <map>
#include <mutex>
#include <condition_variable>
#include <climits>

template<typename Key, typename T>
class ConcurrentMap {
private:
    std::mutex _mu;
    std::condition_variable _cond;
    std::map<Key, T> _mp;
    int capacity;
public:
    ConcurrentMap() {
        this->capacity = INT_MAX;
    }

    ConcurrentMap(int capacity) {
        this->capacity = capacity;
    }

    std::pair<typename std::map<Key,T>::iterator, bool> insert(Key key, T value) {
        std::pair<typename std::map<Key,T>::iterator, bool> retval;
        {
            std::unique_lock<std::mutex> locker(_mu);
            if(_mp.size() >= capacity)
                _cond.wait(locker, [this](){return _mp.size() < capacity;});
            retval =_mp.insert({key, value});
        }
        _cond.notify_one();
        return retval;
    }

    size_t erase(Key key) {
        size_t retval;
        {
            std::unique_lock<std::mutex> locker(_mu);
            if(_mp.find(key) != _mp.end()) {

            }
            else {
                
            }
        }
    }

    bool empty() {
        bool retval;
        {
            std::unique_lock<std::mutex> locker(_mu);
            retval = _mp.empty();
        }
        return retval;
    }
};