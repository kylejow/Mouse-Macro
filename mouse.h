#ifndef MOUSE_H
#define MOUSE_H

#include <windows.h>
#include <atomic>
#include <vector>
#include <thread>
#include <chrono>

#include "screen.h"
#include "cputimer.h"

using std::vector;

void addLocations(std::atomic_bool& stop, vector<POINT>& locations, vector<double>& delays, vector<double>& clickDurations);
void pointToABSInput(MOUSEINPUT& mi, POINT& p, screen& screen);
void clickPoint(POINT& p, screen& screen, double& duration);
void continuousRecord(std::atomic_bool& stop, vector<POINT>& locations, int& polling);
void moveToPoint(POINT& p, screen& screen);
void recordClicks(std::atomic_bool& stop, vector<int>& delays, vector<int>& clickDurations);
void click(int& duration);

#endif