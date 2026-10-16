#ifndef PLAYLIST_STACK_H
#define PLAYLIST_STACK_H

#include "SinglyLinkedList.h"

template <typename T>
class Stack {
public:
    using iterator = typename SinglyLinkedList<T>::iterator;
    using const_iterator = typename SinglyLinkedList<T>::const_iterator;

    bool empty() const { return items_.empty(); }
    std::size_t size() const { return items_.size(); }
    void push(const T& item) { items_.push_front(item); }
    void pushBottom(const T& item) { items_.push_back(item); }
    bool pop() { return items_.pop_front(); }
    T* top() { return items_.at(0); }
    const T* top() const { return items_.at(0); }
    T* at(std::size_t index) { return items_.at(index); }
    const T* at(std::size_t index) const { return items_.at(index); }
    bool removeAt(std::size_t index) { return items_.removeAt(index); }
    iterator begin() { return items_.begin(); }
    iterator end() { return items_.end(); }
    const_iterator begin() const { return items_.begin(); }
    const_iterator end() const { return items_.end(); }
    void swap(Stack& other) noexcept { items_.swap(other.items_); }

private:
    SinglyLinkedList<T> items_;
};

#endif
