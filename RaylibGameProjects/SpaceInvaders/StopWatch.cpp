#include "StopWatch.h"


StopWatch::StopWatch()
{
    StartTime = std::chrono::steady_clock::now();
}
StopWatch::~StopWatch()
{
}
void StopWatch::Start()
{
    StartTime = std::chrono::steady_clock::now();
}
float StopWatch::GetCurrentTime()
{
    std::chrono::milliseconds current_t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - StartTime);
    return current_t.count();
}
float StopWatch::GetTime()
{
    std::chrono::milliseconds current_t = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime);
    return current_t.count();
}
void StopWatch::Stop()
{
    EndTime = std::chrono::steady_clock::now();
}