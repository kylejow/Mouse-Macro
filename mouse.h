#ifndef MOUSE_H
#define MOUSE_H

#include <windows.h>
#include <atomic>
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>

#include "screen.h"
#include "cputimer.h"
#include "program.h"
#include "display.h"
#include "json.hpp"

using std::vector;
using std::thread;
using std::cout;

void pointToABSInput(MOUSEINPUT& mi, POINT& p, screen& screen);
void recordMovements(std::atomic_bool& stop, vector<POINT>& locations);
void moveToPoint(POINT& p, screen& screen);
void recordClicks(std::atomic_bool& stop, vector<int>& delays, vector<int>& clickDurations);
void click(int& duration);
nlohmann::ordered_json recordMouse(void);
void runMovement(vector<POINT>& locations, screen& screen);
void runClicks(vector<int>& clickDurations, vector<int>& delays);

#endif