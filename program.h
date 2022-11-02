#ifndef PROGRAM_H
#define PROGRAM_H

#include <windows.h>
#include <atomic>

void stopProgram(std::atomic_bool& stop);

#endif