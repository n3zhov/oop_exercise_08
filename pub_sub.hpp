//
// Created by nikita on 18.12.2020.
//

#pragma once
#include <mutex>
#include <queue>

template<class T>
class PubSub {
private:
    queue<T> MessageQueue;
    mutex Mutex;
public:
    explicit PubSub() noexcept : MessageQueue(), Mutex() {}
    ~PubSub() {}

    bool Empty() {
        Mutex.lock();
        bool res = MessageQueue.empty();
        Mutex.unlock();
        return res;
    }

    T Front() {
        Mutex.lock();
        T elem = MessageQueue.front();
        Mutex.unlock();
        return elem;
    }

    void Pop() {
        Mutex.lock();
        MessageQueue.pop();
        Mutex.unlock();
    }

    void Push(const T & message) {
        Mutex.lock();
        MessageQueue.push(message);
        Mutex.unlock();
    }
};
