#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
public:
    void push(const T& element){
        std::scoped_lock lock(mutex_);
        bool prev_empty = queue_.empty();

        queue_.push_data(element);

        lock.unlock();
        if (prev_empty) {
            condition_var_.notify_one();
        }
    }

    T& pop() { 
        std::scoped_lock lock(mutex_);

        if(queue_.empty()) {
            condition_var_.wait(lock);
        }

        T& value = queue_.front();
        queue_.pop();

        return value;
    }
private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable condition_var_;
};

#endif // _QUEUE_H_
