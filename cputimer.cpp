// Reference: ECS 36C, UC Davis

#include "cputimer.h"

void cputimer::reset(void){
    begin = std::chrono::high_resolution_clock::now();
}

void cputimer::stop(void){
    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration<double, std::milli>(end - begin).count();
}

double cputimer::elapsed(void){
    return duration;
}