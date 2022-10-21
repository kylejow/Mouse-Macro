// Reference: ECS 36C, UC Davis

#ifndef CPUTIMER_H
#define CPUTIMER_H

#include <chrono>

class cputimer{
    public:
        void reset(void);
        void stop(void);
        int elapsed(void);
    private:
        std::chrono::high_resolution_clock::time_point begin;
        int duration;
};

#endif