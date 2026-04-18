#include <iostream>
#include <string>
#include <sstream>
#include "ArrayQueue.h"

#define MAX_CAPACITY 9999

namespace QueueNamespace {
    class ArrayQueue::Inner {
    private:
        int* arr;         // Pointer to the dynamic array
        int capacity;   // Total current capacity of the array
        int frontIndex; // Index of the front element
        int rearIndex;  // Index of the rear element
        int count;      // Current number of elements in the queue
        void resize();

    public:
        Inner();
        Inner(int initialCapacity);
        Inner(const Inner& other);
        ~Inner();

        int getCapacity() const;
        int getFrontIndex() const;
        int getRearIndex() const;
        int getCount() const;

        Inner& operator=(const Inner& other);
        Inner& operator+=(const int& item);
        Inner& operator-=(int count);
        Inner& operator*=(std::pair<int, int> indexValue);
        int operator[](const int& value) const;
        bool operator==(const Inner& other) const;
        bool operator!=(const Inner& other) const;

        bool operator<(const Inner& other)  const;
        bool operator<=(const Inner& other) const;
        bool operator>(const Inner& other)  const;
        bool operator>=(const Inner& other) const;
        void operator!();

        void enqueue(const int& item);

        void dequeue();

        int front() const;

        int back() const;

        void update(int index, const int& value);

        int peek(int index) const;

        bool isEmpty() const;


        std::string toString() const;
    };

    void ArrayQueue::Inner::resize() {
        int newCapacity = capacity * 2;
        if (newCapacity > MAX_CAPACITY) {
            throw ArrayQueue::QueueCapacityException();
        }
        int* newArr = new int[newCapacity];

        for (int i = 0; i < count; i++) {
            newArr[i] = arr[(frontIndex + i) % capacity];
        }

        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
        frontIndex = 0;
        rearIndex = count - 1;
    }

    ArrayQueue::Inner::Inner() {
        capacity = 5;
        arr = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    ArrayQueue::Inner::Inner(int initialCapacity) {
        capacity = initialCapacity;
        arr = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    ArrayQueue::Inner::Inner(const Inner& other)
    : capacity(other.capacity),
      frontIndex(0),
      rearIndex(other.count - 1),
      count(other.count)
    {
        arr = new int[capacity];
        for (int i = 0; i < count; i++)
            arr[i] = other.arr[(other.frontIndex + i) % other.capacity];
    }

    ArrayQueue::Inner::~Inner() {
        delete[] arr;
    }

    int ArrayQueue::Inner::getCapacity() const {
        return capacity;
    }
    int ArrayQueue::Inner::getFrontIndex() const {
        return frontIndex;
    }
    int ArrayQueue::Inner::getRearIndex() const {
        return rearIndex;
    }
    int ArrayQueue::Inner::getCount() const {
        return count;
    }

    ArrayQueue::Inner& ArrayQueue::Inner::operator=(const Inner& other) {
        if (this == &other) return *this;
        delete[] arr;

        capacity = other.capacity;
        count = other.count;
        frontIndex = 0;
        rearIndex = count - 1;
        arr = new int[capacity];
        for (int i = 0; i < count; i++) {
            arr[i] = other.arr[(other.frontIndex + i) % other.capacity];
        }
        return *this;
    }
    ArrayQueue::Inner& ArrayQueue::Inner::operator+=(const int& item) {
        enqueue(item);
        return *this;
    }

    ArrayQueue::Inner& ArrayQueue::Inner::operator-=(int count) {
        for (int i = 0; i < count; i++) dequeue();
        return *this;
    }

    ArrayQueue::Inner& ArrayQueue::Inner::operator*=(std::pair<int, int> indexValue) {
        int idx = indexValue.first;
        if (idx < 0 || idx >= count)
            throw std::out_of_range("Index out of range.");
        arr[(frontIndex + idx) % capacity] = indexValue.second;
        return *this;
    }

    int ArrayQueue::Inner::operator[](const int& value) const {
        for (int i = 0; i < count; i++)
            if (arr[(frontIndex + i) % capacity] == value) {
                return i;
            }
        return -1;
    }
    bool ArrayQueue::Inner::operator==(const Inner& other) const {
        if (count != other.count) return false;
        for (int i = 0; i < count; i++) {
            if (arr[(frontIndex+i)%capacity] != other.arr[(other.frontIndex+i)%other.capacity]) {
                return false;
            }
        }
        return true;
    }
    bool ArrayQueue::Inner::operator!=(const Inner& other) const {
        return !(*this == other);
    }
    bool ArrayQueue::Inner::operator<(const Inner& other)  const {
        if (count < other.count) {
            return true;
        }
        if (count > other.count) {
            return false;
        }
        for (int i = 0; i < count; i++) {
            if (arr[(frontIndex+i)%capacity] < other.arr[(other.frontIndex+i)%other.capacity]) {
                return true;
            }
            if (arr[(frontIndex+i)%capacity] > other.arr[(other.frontIndex+i)%other.capacity]) {
                return false;
            }
        }
        return false;
    }
    bool ArrayQueue::Inner::operator<=(const Inner& other) const {
        return (*this == other || *this < other);
    }
    bool ArrayQueue::Inner::operator>(const Inner& other)  const {
        if (count > other.count) {
            return true;
        }
        if (count < other.count) {
            return false;
        }
        for (int i = 0; i < count; i++) {
            if (arr[(frontIndex+i)%capacity] > other.arr[(other.frontIndex+i)%other.capacity]) {
                return true;
            }
            if (arr[(frontIndex+i)%capacity] < other.arr[(other.frontIndex+i)%other.capacity]) {
                return false;
            }
        }
        return false;
    }
    bool ArrayQueue::Inner::operator>=(const Inner& other) const {
        return (*this == other || *this > other);
    }
    void ArrayQueue::Inner::operator!() {
        frontIndex = 0;
        rearIndex = -1;
        count = 1;
    }

    void ArrayQueue::Inner::enqueue(const int& item) {
        if (count == capacity) {
            resize();
        }
        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = item;
        count++;
    }
    void ArrayQueue::Inner::dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty.");
        }
        frontIndex = (frontIndex + 1) % capacity;
        count--;
    }
    int ArrayQueue::Inner::front() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty.");
        }
        return arr[frontIndex];
    }
    int ArrayQueue::Inner::back() const {
        if (isEmpty()) throw std::out_of_range("Queue is empty.");
        return arr[rearIndex];
    }
    void ArrayQueue::Inner::update(int index, const int& value) {
        if (index < 0 || index >= count)
            throw std::out_of_range("Index out of range.");
        arr[(frontIndex + index) % capacity] = value;
    }
    int ArrayQueue::Inner::peek(int index) const {
        if (index < 0 || index >= count)
            throw std::out_of_range("Index out of range.");
        return arr[(frontIndex + index) % capacity];
    }
    bool ArrayQueue::Inner::isEmpty() const {
        return count == 0;
    }
    std::string ArrayQueue::Inner::toString() const {
        std::ostringstream oss;
        oss << "Queue[size=" << count << ", capacity=" << capacity;
        if (!isEmpty()) {
            oss << ", front=" << front();
            oss << ", back=" << arr[rearIndex];
        }
        oss << "]";
        return oss.str();
    }

    class QueueCapacityException : public std::runtime_error {
    public:
        explicit QueueCapacityException()
            : std::runtime_error("Queue exceeded max allowed capacity") {};
    };

    ArrayQueue::ArrayQueue() {
        impl = new ArrayQueue::Inner();
    }

    ArrayQueue::ArrayQueue(int initialCapacity){
        impl = new ArrayQueue::Inner(initialCapacity);
    }
    ArrayQueue::ArrayQueue(const ArrayQueue& other){
        impl = new ArrayQueue::Inner(*(other.impl));
    }
    ArrayQueue::~ArrayQueue(){
        delete impl;
    }

    int ArrayQueue::getCapacity() const {
        return impl->getCapacity();
    }
    int ArrayQueue::getFrontIndex() const {
        return impl->getFrontIndex();
    }
    int ArrayQueue::getRearIndex() const {
        return impl->getRearIndex();
    }
    int ArrayQueue::getCount() const {
        return impl->getCount();
    }


    ArrayQueue &ArrayQueue::operator=(const ArrayQueue &other) {
        if (&other != this) {
            delete impl;
            impl = new ArrayQueue::Inner(*(other.impl));
        }
        return *this;
    }
    ArrayQueue& ArrayQueue::operator+=(const int& item) {
        *impl += item;
        return *this;
    }
    ArrayQueue& ArrayQueue::operator-=(int count) {
        *impl -= count;
        return *this;
    }
    ArrayQueue& ArrayQueue::operator*=(std::pair<int, int> indexValue) {
        *impl *= indexValue;
        return *this;
    }
    int ArrayQueue::operator[](const int& value) const {
        return (*impl)[value];
    }
    bool ArrayQueue::operator==(const ArrayQueue& other) const {
        return *impl == *(other.impl);
    }
    bool ArrayQueue::operator!=(const ArrayQueue& other) const {
        return *impl != *(other.impl);
    }
    bool ArrayQueue::operator<(const ArrayQueue& other)  const {
        return *impl < *(other.impl);
    }
    bool ArrayQueue::operator<=(const ArrayQueue& other) const {
        return *impl <= *(other.impl);
    }
    bool ArrayQueue::operator>(const ArrayQueue& other)  const {
        return *impl > *(other.impl);
    }
    bool ArrayQueue::operator>=(const ArrayQueue& other) const {
        return *impl >= *(other.impl);
    }
    void ArrayQueue::operator!() {
        impl->operator!();
    }

    void ArrayQueue::enqueue(const int& item) {
        impl->enqueue(item);
    }
    void ArrayQueue::dequeue() {
        impl->dequeue();
    }
    int ArrayQueue::front() const {
        return impl->front();
    }
    int ArrayQueue::back() const {
        return impl->back();
    }
    void ArrayQueue::update(int index, const int& value) {
        impl->update(index, value);
    }
    int ArrayQueue::peek(int index) const {
        return impl->peek(index);
    }
    bool ArrayQueue::isEmpty() const {
        return impl->isEmpty();
    }
    std::string ArrayQueue::toString() const {
        return impl->toString();
    }

    ArrayQueue::QueueCapacityException::QueueCapacityException()
        : std::runtime_error("Queue exceeded max allowed capacity") {
    }
};
