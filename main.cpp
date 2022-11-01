/*References
get cursor pos  https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getcursorpos
POINT           https://learn.microsoft.com/en-us/previous-versions/dd162805(v=vs.85)
get key state   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getkeystate
mouse input     https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-mouseinput
INPUT           https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-input
send input      https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput
MOUSEINPUT      https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-mouseinput
key codes       https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

TODO:
option to remove all delays
edit delays
json saved macros
keyboard support
multiple monitor support
*/

#include <windows.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <vector>

#include "display.h"
#include "screen.h"
#include "mouse.h"
#include "menu.h"
#include "json.hpp"

using std::cout;
using std::cin;
using std::string;
using std::thread;
using std::vector;
using std::ref;

void stopProgram(std::atomic_bool& stop);

int main(){
    std::ifstream load("saved.json");
    nlohmann::ordered_json savedMacros = nlohmann::ordered_json::parse(load);
    load.close();
    string input;
    while(1){
        system("cls");
        cout << "1. Run saved macro\n"
             << "2. Record new macro\n"
             << "3. View macros\n"
             << "4. Delete macro\n"
             << "\n\nq to quit\n\n";
        cin >> input;
        if(input == "1"){

        }else if(input == "2"){

        }else if(input == "3"){
            if(noSavedMacros(savedMacros)){
                    continue;
            }
            system("cls");
            printSavedTargets(savedMacros);
            system("pause");
            continue;
        }else if(input == "4"){

        }else if(input == "q"){
            exit(0);
        }
    }
    exit(0);



    system("cls");
    cout << "\nPress shift to start recording\n";
    while(!(GetKeyState(VK_SHIFT) & 0x8000)){};

    int polling = 1;
    vector<POINT> locations;
    vector<int> delays;
    vector<int> clickDurations;
    screen screen;
    std::atomic_bool stop = false;
    thread stopThread(stopProgram, ref(stop));
    thread recordClick(recordClicks, ref(stop), ref(delays), ref(clickDurations));
    thread recordMovement(recordMovements, ref(stop), ref(locations), ref(polling));
    system("cls");
    setCursor(false);
    POINT p;
    while(!stop){
        GetCursorPos(&p);
        cout << "Current Location: " << p.x << ", " << p.y << "             \n";
        cout << "\n\nalt + q to stop\n";
        clearScreen();
    }
    stopThread.join();
    recordClick.join();
    recordMovement.join();
    setCursor(true);
    system("cls");

    cout << "\nPress shift to run\n";
    while(!(GetKeyState(VK_SHIFT) & 0x8000)){};

    // thread mouseMovement(runMovement, ref(locations), ref(screen), ref(polling));
    // runClicks(clickDurations, delays);
    // mouseMovement.join();
    nlohmann::ordered_json savedMacro;
    savedMacro["1"]["Name"] = "Test macro 1";
    savedMacro["1"]["delays"] = delays;
    savedMacro["1"]["clickDurations"] = clickDurations;
    vector<long> tmp = {NULL, NULL};
    for(unsigned long long int i = 0; i < locations.size(); i++){
        tmp[0] = locations[i].x;
        tmp[1] = locations[i].y;
        savedMacro["1"]["locations"][i] = tmp;
    }
    std::ofstream save("saved.json");
    save << savedMacro.dump(1) + "\n";
    save.close();
    return 0;
}

void stopProgram(std::atomic_bool& stop){
    while(1){
        if((GetKeyState(VK_MENU) & 0x8000) && (GetKeyState(0x51) & 0x8000)){
            stop = true;
            return;
        }
    }
}