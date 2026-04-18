#include <iostream>
#include <utility>
#include "ArrayQueue.h"

using namespace QueueNamespace;

int main() {
    try {
        ArrayQueue q1(4);
        std::cout << "Created q1: " << q1.toString() << "\n";

        q1.enqueue(10);
        q1 += 20;
        q1 += 30;
        std::cout << "q1: " << q1.toString() << "\n";

        std::cout << q1.toString();

        std::cout << "Front: " << q1.front() << ", Back: " << q1.back() << "\n";
        std::cout << "Peek at index 1: " << q1.peek(1) << "\n";
        std::cout << "Search for value 20: " << q1[20] << "\n";

        q1.update(0, 15);
        q1 *= std::make_pair(1, 25);
        std::cout << "q1: " << q1.toString() << "\n";

        ArrayQueue q3(2);
        q3 = q1;

        q1.dequeue();
        q1.dequeue();
        q1.dequeue();
        std::cout << "\nAttempting an invalid dequeue\n";
        q1.dequeue(); // This will throw std::out_of_range

    } catch (const std::exception& e) {
        std::cout << "\nException: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "\nCaught an unknown exception!" << std::endl;
    }

    return 0;
}
