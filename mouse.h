#ifndef MOUSE_H
#define MOUSE_H

#include <windows.h>
#include <atomic>
#include <vector>

#include "screen.h"
#include "cputimer.h"

using std::vector;

void addLocations(std::atomic_bool& stop, vector<POINT>& locations, vector<double>& delays, vector<double>& clickDurations);
void pointToABSInput(MOUSEINPUT& mi, POINT& p, screen& screen);
void clickPoint(POINT& p, screen& screen, double& duration);

#endif