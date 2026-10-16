#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <cstddef>
#include <utility>

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T value;
        Node* next;
        explicit Node(const T& item) : value(item), next(nullptr) {}
    };

public:
    class iterator {
        friend class SinglyLinkedList;
        Node* node_;
        explicit iterator(Node* node) : node_(node) {}
    public:
        iterator() : node_(nullptr) {}
        T& operator*() const { return node_->value; }
        T* operator->() const { return &node_->value; }
        iterator& operator++() { node_ = node_->next; return *this; }
        bool operator!=(const iterator& other) const { return node_ != other.node_; }
        bool operator==(const iterator& other) const { return node_ == other.node_; }
    };

    class const_iterator {
        friend class SinglyLinkedList;
        const Node* node_;
        explicit const_iterator(const Node* node) : node_(node) {}
    public:
        const_iterator() : node_(nullptr) {}
        const T& operator*() const { return node_->value; }
        const T* operator->() const { return &node_->value; }
        const_iterator& operator++() { node_ = node_->next; return *this; }
        bool operator!=(const const_iterator& other) const { return node_ != other.node_; }
        bool operator==(const const_iterator& other) const { return node_ == other.node_; }
    };

    SinglyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

    SinglyLinkedList(const SinglyLinkedList& other) : SinglyLinkedList() {
        for (const T& item : other) push_back(item);
    }

    SinglyLinkedList(SinglyLinkedList&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    SinglyLinkedList& operator=(SinglyLinkedList other) {
        swap(other);
        return *this;
    }

    ~SinglyLinkedList() { clear(); }

    void swap(SinglyLinkedList& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

    bool empty() const { return size_ == 0; }
    std::size_t size() const { return size_; }

    void push_back(const T& item) {
        Node* node = new Node(item);
        if (tail_) tail_->next = node;
        else head_ = node;
        tail_ = node;
        ++size_;
    }

    void push_front(const T& item) {
        Node* node = new Node(item);
        node->next = head_;
        head_ = node;
        if (!tail_) tail_ = node;
        ++size_;
    }

    bool pop_front() {
        if (!head_) return false;
        Node* old = head_;
        head_ = head_->next;
        delete old;
        --size_;
        if (!head_) tail_ = nullptr;
        return true;
    }

    T* at(std::size_t index) {
        Node* node = nodeAt(index);
        return node ? &node->value : nullptr;
    }

    const T* at(std::size_t index) const {
        const Node* node = nodeAt(index);
        return node ? &node->value : nullptr;
    }

    bool removeAt(std::size_t index) {
        if (index >= size_) return false;
        if (index == 0) return pop_front();
        Node* previous = nodeAt(index - 1);
        Node* removed = previous->next;
        previous->next = removed->next;
        if (removed == tail_) tail_ = previous;
        delete removed;
        --size_;
        return true;
    }

    bool move(std::size_t from, std::size_t to) {
        if (from >= size_ || to >= size_ || from == to) return from == to && from < size_;
        Node* moving = nullptr;
        if (from == 0) {
            moving = head_;
            head_ = head_->next;
            if (moving == tail_) tail_ = nullptr;
        } else {
            Node* previous = nodeAt(from - 1);
            moving = previous->next;
            previous->next = moving->next;
            if (moving == tail_) tail_ = previous;
        }

        if (to == 0) {
            moving->next = head_;
            head_ = moving;
            if (!tail_) tail_ = moving;
        } else {
            Node* previous = nodeAt(to - 1);
            moving->next = previous->next;
            previous->next = moving;
            if (!moving->next) tail_ = moving;
        }
        return true;
    }

    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(nullptr); }
    const_iterator begin() const { return const_iterator(head_); }
    const_iterator end() const { return const_iterator(nullptr); }

    void clear() {
        while (head_) {
            Node* next = head_->next;
            delete head_;
            head_ = next;
        }
        tail_ = nullptr;
        size_ = 0;
    }

private:
    Node* head_;
    Node* tail_;
    std::size_t size_;

    Node* nodeAt(std::size_t index) {
        if (index >= size_) return nullptr;
        Node* node = head_;
        while (index--) node = node->next;
        return node;
    }

    const Node* nodeAt(std::size_t index) const {
        if (index >= size_) return nullptr;
        const Node* node = head_;
        while (index--) node = node->next;
        return node;
    }
};

#endif
