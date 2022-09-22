#pragma once

#include <chrono>
#include <ctime>

template <typename Duration>
class Timer
{
protected:
    using SteadyClock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<SteadyClock>;

    TimePoint startTime;
public:
    constexpr Timer() = default;
    constexpr ~Timer() = default;

    constexpr std::time_t getElapsedTime()
    {
        TimePoint currentTime = SteadyClock::now();
        Duration elapsedTime = std::chrono::duration_cast<Duration>(currentTime - this->startTime);

        return static_cast<std::time_t>(elapsedTime.count());
    }

    constexpr void startTimer()
    {
        this->startTime = SteadyClock::now();
    }
};

using MicrosecondTimer = Timer<std::chrono::microseconds>;
using MillisecondTimer = Timer<std::chrono::milliseconds>;

using DefaultTimer = MicrosecondTimer;
