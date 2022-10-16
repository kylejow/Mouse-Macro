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
record duration
add delay/option to remove all delays
csv saved macros
keyboard support
*/

#include <windows.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

#include "display.h"
#include "screen.h"
#include "mouse.h"

using std::cout;
using std::cin;
using std::thread;
using std::vector;

void stopProgram(std::atomic_bool& stop);

int main(){
    vector<POINT> locations;
    screen screen((double)GetSystemMetrics(SM_CXSCREEN),
                  (double)GetSystemMetrics(SM_CYSCREEN));
    std::atomic_bool stop = false;
    thread stopThread(stopProgram, ref(stop));
    thread recordClicks(addLocations, ref(stop), ref(locations));
    system("cls");
    setCursor(false);
    POINT p;
    while(!stop){
        GetCursorPos(&p);
        cout << p.x << ", " << p.y << "             \n";
        cout << locations.size();
        cout << "\n\nalt + q to stop\n";
        clearScreen();
    }
    stopThread.join();
    recordClicks.join();
    setCursor(true);
    system("cls");
    for(auto iter = locations.begin(); iter != locations.end(); iter++){
        printPOINT(*iter);
    }
    cout << "\nPress enter to click these points\n";
    while(!(GetKeyState(VK_RETURN) & 0x8000)){};
    for(auto iter = locations.begin(); iter != locations.end(); iter++){
        clickPoint(*iter, screen);
        Sleep(200);
    }
}

void stopProgram(std::atomic_bool& stop){
    while(1){
        if((GetKeyState(VK_MENU) & 0x8000) && (GetKeyState(0x51) & 0x8000)){
            stop = true;
            return;
        }
    }
}
