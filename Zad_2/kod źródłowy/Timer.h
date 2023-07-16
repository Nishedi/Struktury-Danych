#pragma once
#include <chrono>
using namespace std::chrono;
class Timer
{
    high_resolution_clock::time_point t0;
    high_resolution_clock::time_point t1;
public:
    void start() {
        t0 = high_resolution_clock::now();
    }
    void stop() {
        t1 = high_resolution_clock::now();
    }

    uint64_t timeperiod() {
        duration< double > fs = t1 - t0;
        return (uint64_t)(fs.count() * 1000000);
    }
};

