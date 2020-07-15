#pragma once
#include <chrono>

class StopWatch
{
private:
    std::chrono::steady_clock::time_point StartTime;
    std::chrono::steady_clock::time_point EndTime;
public:
    StopWatch();
    ~StopWatch();
    void Start();
    float GetCurrentTime();
    float GetTime();
    void Stop();
};
