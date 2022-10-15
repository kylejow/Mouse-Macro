#ifndef MOUSE_H
#define MOUSE_H

#include <windows.h>
#include <atomic>
#include <vector>
#include "screen.h"

using std::vector;

void addLocations(std::atomic_bool& stop, vector<POINT>& locations);
void pointToABSInput(MOUSEINPUT& mi, POINT& p, screen& screen);
void clickPoint(POINT& p, screen& screen);

#endif