#ifndef MENU_H
#define MENU_H

#include <windows.h>
#include <vector>
#include <iostream>

#include "json.hpp"

using std::string;
using std::cout;
using std::cin;
using std::vector;

void printSavedTargets(nlohmann::ordered_json& savedMacros);
bool noSavedMacros(nlohmann::ordered_json& savedMacros);
int chooseFromSaved(nlohmann::ordered_json savedMacros);

#endif