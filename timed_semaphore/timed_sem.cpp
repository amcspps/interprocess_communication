#include "timed_sem.hpp"
#include <cstring>
TimedSemaphore::TimedSemaphore(int init_value)  {
    if (sem_init(&semaphore_, 1, init_value) == -1) {
        std::cout << "semaphore initialization error" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void TimedSemaphore::wait(int timeout_seconds) {
        struct timespec current_time;
        if (clock_gettime(CLOCK_REALTIME, &current_time) == -1) {
            std::cout << "Error getting current time." << std::endl;
            exit(EXIT_FAILURE);
        }
        struct timespec expiration_time;
        expiration_time.tv_sec = current_time.tv_sec + timeout_seconds;
        expiration_time.tv_nsec = 0;
        int result = sem_timedwait(&semaphore_, &expiration_time);
        if (result == 0) {
            std::cout << "Semaphore acquired successfully!" << std::endl;
        } else if (result == -1) {
            std::cout << "Semaphore wait timed out! errno: " << strerror(errno) << std::endl;
            exit(EXIT_FAILURE);
        }
    }

void TimedSemaphore::post() {
        sem_post(&semaphore_);
}

TimedSemaphore::~TimedSemaphore() {
    sem_destroy(&semaphore_);
}