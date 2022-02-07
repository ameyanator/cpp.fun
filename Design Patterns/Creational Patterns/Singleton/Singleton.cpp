#include <string>
#include <mutex>

class Singleton {

private:
static Singleton *pinstance_;
static std::mutex mutex_;

protected:
    Singleton(const std::string value) {
        value_ = value;
        // pinstance_ = nullptr;
    }
    ~Singleton() {}
    std::string value_;

public:
    Singleton(Singleton &other) = delete;

    void operator=(const Singleton &) = delete;

    static Singleton* GetInstance(const std::string value) {
        std::lock_guard<std::mutex> lock(mutex_);
        if(pinstance_ == nullptr) {
            pinstance_ = new Singleton(value);
        }
        return pinstance_;
    }

    std::string value() const {
        return value_;
    }
};


Singleton* Singleton::pinstance_{nullptr};
std::mutex Singleton::mutex_;