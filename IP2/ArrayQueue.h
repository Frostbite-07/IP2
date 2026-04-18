/**
* @file ArrayQueue.h
 * @brief Definition of a circular-array based Queue ADT using the Pimpl idiom.
 * @note Google Gemini was used to generate the simple version of the array-based Queue ADT with the functions enqueue, dequeue, front, back. Gemini was also used as a learning tool
for non-coding purposes, such as how to write the Makefile and documentation in the .h file.
 * @author Matas Čekanauskas
 * @date 2026-03-27
 */

#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

#include <iostream>
#include <string>
#include <sstream>

#define MAX_CAPACITY 9999

namespace QueueNamespace {
    /**
     * @class ArrayQueue
     * @brief A Queue implementation that supports CRUD operations via operators.
     * This class uses a Pointer to Implementation (Pimpl) to hide internal data structures.
     * It has a maximum capacity of 9999 elements.
     */

    class ArrayQueue {
    private:
        class Inner;
        Inner* impl;

    public:
        ArrayQueue();
        ArrayQueue(int initialCapacity);
        ArrayQueue(const ArrayQueue& other);
        ~ArrayQueue();

        int getCapacity() const;
        int getFrontIndex() const;
        int getRearIndex() const;
        int getCount() const;

        /**
         * @brief Assignment operator for the ArrayQueue. Replaces current contents with a deep copy of another ArrayQueue object.
         * @param other Array object to be copied
         * @return A reference to the current object.
         */
        ArrayQueue& operator=(const ArrayQueue& other);
        /**
         * @brief Operator for the ArrayQueue. Enqueues an item into the given ArrayQueue object.
         * @param item Integer to be enqueued.
         * @return A reference to the current object after enqueue.
         */
        ArrayQueue& operator+=(const int& item);
        /**
         * @brief Operator for the ArrayQueue. Dequeues an item from the given ArrayQueue object.
         * @param count Amount of items to be dequeued
         * @return A reference to the current object after dequeue.
         */
        ArrayQueue& operator-=(int count);
        /**
         * @brief Operator for the ArrayQueue. Updates an item in the given ArrayQueue object, meaning changing the value of an item at a given index.
         * @param indexValue A pair of integers, the first one denoting the index of the item and the second denoting the new value of the item.
         * @throw std::out_of_range Thrown when the first member of the pair (the index) is negative or more than the total count of items.
         * @return A reference to the current object after update.
         */
        ArrayQueue& operator*=(std::pair<int, int> indexValue);
        /**
         * @brief Operator for the ArrayQueue. Used for finding the index of a given value in the ArrayQueue object.
         * @param value A value to search for the index of.
         * @return The index of the value if found or -1 of the value is not in the queue.
         */
        int operator[](const int& value) const;
        //Comparison operators
        /**
         * @brief Operator for the ArrayQueue. Compares every element of 2 ArrayQueue objects to see if they are identical.
         * @param other Reference to the second ArrayQueue object to compare against.
         * @return true if objects are equal, false otherwise.
         */
        bool operator==(const ArrayQueue& other) const;
        /**
         * @brief Operator for the ArrayQueue. Opposite of the == operator, compares every element of 2 ArrayQueue objects to see if they are different.
         * @param other Reference to the second ArrayQueue object to compare against.
         * @return true if objects are not equal, false otherwise.
         */
        bool operator!=(const ArrayQueue& other) const;
        /**
         * @brief Operator for the ArrayQueue. Compares the count of 2 ArrayQueue objects.
         * @param other Reference to the second ArrayQueue object to compare against.
         * @return true if first object's count is smaller than the second, false otherwise.
         */
        bool operator<(const ArrayQueue& other)  const;
        /**
         * @brief Operator for the ArrayQueue. Compares the count of 2 ArrayQueue objects.
         * @param other Reference to the second ArrayQueue object to compare against.
         * @return true if first object's count is smaller or equal than the second, false otherwise.
         */
        bool operator<=(const ArrayQueue& other) const;
        /**
         * @brief Operator for the ArrayQueue. Compares the count of 2 ArrayQueue objects.
         * @param other Reference to the second ArrayQueue object to compare against.
         * @return true if first object's count is greater than the second, false otherwise.
         */
        bool operator>(const ArrayQueue& other)  const;
        /**
         * @brief Operator for the ArrayQueue. Compares the count of 2 ArrayQueue objects.
         * @param other Reference to the second ArrayQueue object to compare against.
         * @return true if first object's count is greater of equal than the second, false otherwise.
         */
        bool operator>=(const ArrayQueue& other) const;

        /**
         * @brief Operator for the ArrayQueue. Clean/reset operator.
         */
        void operator!();

        /**
         * @brief Adds an item to the back of the queue.
         * @param item The integer value to be inserted.
         * @throw QueueCapacityException If the queue is full and cannot resize beyond MAX_CAPACITY.
         */
        void enqueue(const int& item);

        /**
         * @brief REmoves the front element from the queue.
         * @throw std::out_of_range If the queue is empty.
         */
        void dequeue();

        /**
         * @brief Finds and returns the item at the front of the queue.
         * @throw std::out_of_range If the queue is empty.
         * @return Value of the item at the front of the queue.
         */
        int front() const;

        /**
         * @brief Finds and returns the item at the back of the queue.
         * @throw std::out_of_range If the queue is empty.
         * @return Value of the item at the back of the queue.
         */
        int back() const;

        /**
         * @brief Updates an item in the given ArrayQueue object, meaning changing the value of an item at a given index.
         * @param index, value Index of the item to be updated, new value of the item.
         * @throw std::out_of_range Thrown when the first member of the pair (the index) is negative or more than the total count of items.
         */
        void update(int index, const int& value);

        /**
         * @brief Used for finding the index of a given value in the ArrayQueue object.
         * @param index A value to search for the index of.
         * @return The index of the value if found or -1 of the value is not in the queue.
         */
        int peek(int index) const;

        /**
         * @brief Checks whether the object is empty, meaning no items are present.
         * @return true if the object is empty, false otherwise.
         */
        bool isEmpty() const;

        /**
         * @brief Gets information about the object, adds labels to it for readability and constructs one string.
         * @return A string value containing the information of the object.
         */
        std::string toString() const;

        /**
         * @brief Custom exception for maximum capacity limits.
         */
        class QueueCapacityException : public std::runtime_error {
        public:
            explicit QueueCapacityException();
        };
    };
};

#endif