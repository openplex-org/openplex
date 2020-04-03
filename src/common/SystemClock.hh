// This file is a part of std-adiog project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <chrono>
#include <cstdint>
#include <thread>


struct SystemClock
{
public:
    static uint64_t seconds()
    {
        std::chrono::time_point<std::chrono::system_clock> timer = std::chrono::system_clock::now();
        uint64_t secondsSinceEpoch =
                std::chrono::duration_cast<std::chrono::seconds>(timer.time_since_epoch()).count();
        return secondsSinceEpoch;
    }

    static uint64_t millis()
    {
        std::chrono::time_point<std::chrono::system_clock> timer = std::chrono::system_clock::now();
        uint64_t millisSinceEpoch =
            std::chrono::duration_cast<std::chrono::milliseconds>(timer.time_since_epoch()).count();
        return millisSinceEpoch;
    }

    static uint64_t micros()
    {
        std::chrono::time_point<std::chrono::system_clock> timer = std::chrono::system_clock::now();
        uint64_t microsSinceEpoch =
            std::chrono::duration_cast<std::chrono::microseconds>(timer.time_since_epoch()).count();
        return microsSinceEpoch;
    }

    static int get_fps() {
        static int FPS = 0;
        static int fps = 0;
        static int last = SystemClock::seconds();
        fps++;
        if (last != SystemClock::seconds()) {
            last = SystemClock::seconds();
            FPS = fps;
            fps = 0;
        }
        return FPS;
    }

    static void keep_fps() {
        static int FPS = 60;
        static int micros = 1'000'000 / FPS;
        static std::chrono::time_point<std::chrono::system_clock> next = std::chrono::system_clock::now();
        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        if (now < next) {
            std::this_thread::sleep_until(next);
        }
        next += std::chrono::microseconds(micros);
    }
};

