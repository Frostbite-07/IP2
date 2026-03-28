#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cassert>
#include "ArrayQueue.h"

using namespace QueueNamespace;

void logOutput(std::ofstream& logFile, const std::string& message) {
    std::cout << message << "\n";
    if (logFile.is_open()) logFile << message << "\n";
}

std::string memberList(int count, ArrayQueue q) {
    std::string temp = "Array members: [ ";
    for (int i = 0; i < count; ++i) {
        temp += std::to_string(q.peek(i)) + " ";
    }
    temp += "]";
    return temp;
}

int main() {
    std::ofstream logFile("log.txt");
    try {
        logOutput(logFile, "        ARRAYQUEUE TEST START        ");

        ArrayQueue q(5);

        // Test 1
        logOutput(logFile, "Test 1: Basic operations");
        logOutput(logFile, "q += 20");
        q += 20;
        logOutput(logFile, memberList(q.getCount(), q));
        logOutput(logFile, "q += 50");
        q += 50;
        logOutput(logFile, memberList(q.getCount(), q));
        logOutput(logFile, "q += 34");
        q += 34;
        logOutput(logFile, memberList(q.getCount(), q));
        logOutput(logFile, "q += 46");
        q += 46;
        logOutput(logFile, memberList(q.getCount(), q));
        assert(q.peek(2) == 34);
        logOutput(logFile, "Test 1.1: += operator PASS");
        logOutput(logFile, "q *= (1, 67)");
        q *= std::make_pair(1, 67);
        assert(q.peek(1) == 67);
        logOutput(logFile, "Test 1.2: *= operator PASS");
        logOutput(logFile, "q -= 2");
        q -= 2;
        assert(q.getCount() == 2);
        logOutput(logFile, "Test 1.3: -= operator PASS");

        logOutput(logFile, memberList(q.getCount(), q) + "\n");

        ArrayQueue q2 = q;
        logOutput(logFile, "Copied q2: " + q2.toString());
        logOutput(logFile, memberList(q2.getCount(), q));
        std::string comp = (q == q2 ? "Test 1.4: = operator PASS" : "Test 1.4: = operator FAIL");
        logOutput(logFile, "q == q2: " + comp);
        logOutput(logFile, "q2 += 40");
        q2 += 40;
        comp = (q < q2 ? "Yes" : "No");
        logOutput(logFile, "q < q2: " + comp);
        logOutput(logFile, "Dequeue q2");
        q2.dequeue();
        logOutput(logFile, "q2 -= 1");
        q2 -= 1;
        logOutput(logFile, "q2: " + q2.toString());
        comp = (q.isEmpty() ? "Yes" : "No");
        logOutput(logFile, "Is q empty? " + comp);
        logOutput(logFile, "!q");
        !q;
        comp = (q.isEmpty() ? "Test 1.5: ! operator PASS" : "Test 1.5: ! operator FAIL");
        logOutput(logFile, comp);
        logOutput(logFile, q2.toString());
        if (q2.front() == 34) logOutput(logFile, "Test 1: PASS");
        else logOutput(logFile, "Test 1: FAIL");

        // Test 2
        logOutput(logFile, "Test 2: Custom exception");
        try {
            ArrayQueue bigQ(5000);
            for (int i = 0; i < 5000; ++i) {
                bigQ += i;
            }
            logOutput(logFile, bigQ.toString());
            bigQ += 0;
            logOutput(logFile, "Test 2: FAIL No exception thrown");
        } catch (const ArrayQueue::QueueCapacityException& e) {
            logOutput(logFile, "Test 2: PASS Caught: " + std::string(e.what()));
        }


        logOutput(logFile, "           TEST SUITE COMPLETED SUCCESSFULLY       ");

    } catch (const std::exception& e) {
        logOutput(logFile, "Unexpected exception: " + std::string(e.what()));
    } catch (...) {
        logOutput(logFile, "An unknown error occurred");
    }

    logFile.close();
    return 0;
}