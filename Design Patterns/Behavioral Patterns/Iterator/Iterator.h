#include <iostream>
#include <vector>
#include <string>

template<typename T, typename U>
class Iterator {
public:
    typedef typename std::vector<T>::iterator iter_type;
    Iterator(U* p_data, bool reverse = false) : m_p_data(p_data) {
        m_it_ = m_p_data->m_data_.begin();
    }

    void First() {
        m_it_ = m_p_data->m_data_.begin();
    }

    void Next() {
        m_it_++;
    }

    bool IsDone() {
        return m_it_ == m_p_data->m_data_.end();
    }

    iter_type Current() {
        return m_it_;
    }

private:
    U* m_p_data;
    iter_type m_it_;
};