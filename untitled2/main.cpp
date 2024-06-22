#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <random>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
std::queue<std::string> studentQueue;
bool allStudentsPassed = false;

int getRandomGrade() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, 5);
    return dis(gen);
}

int getRandomTime() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 5);
    return dis(gen);
}

void examinerThread(int examinerId) {
    while (true) {
        std::string studentName;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] { return allStudentsPassed || !studentQueue.empty(); });

            if (allStudentsPassed) {
                break;
            }

            studentName = studentQueue.front();
            studentQueue.pop();
        }

        int grade = getRandomGrade();
        std::cout << "Exam " << studentName << " received an assessment " << grade << " examenator " << examinerId << std::endl;

        if (grade < 3) {
            std::lock_guard<std::mutex> lock(mtx);
            studentQueue.push(studentName);
        }

        cv.notify_all();
        std::this_thread::sleep_for(std::chrono::seconds(getRandomTime()));
    }
}

int main() {
    std::vector<std::string> students = {"Ivanov", "Petrov", "Sidorov", "Kozlov", "Sokolov"};
    for (const auto& student : students) {
        studentQueue.push(student);
    }

    int numExaminers = 2;
    std::vector<std::thread> examinerThreads;
    for (int i = 0; i < numExaminers; ++i) {
        examinerThreads.emplace_back(examinerThread, i + 1);
    }

    while (!studentQueue.empty()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        allStudentsPassed = true;
    }
    cv.notify_all();

    for (auto& thread : examinerThreads) {
        thread.join();
    }

    return 0;
}