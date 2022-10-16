// Reference: ECS 36C, UC Davis

#ifndef CPUTIMER_H
#define CPUTIMER_H

#include <chrono>

class cputimer{
    public:
        void reset(void);
        void stop(void);
        double elapsed(void);
    private:
        std::chrono::high_resolution_clock::time_point begin;
        double duration;
};

#endif