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
csv saved macros
keyboard support
multiple monitor support
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
using std::ref;

void stopProgram(std::atomic_bool& stop);
void printVect(vector<double>& vect){
    auto iter = vect.begin();
    while(iter != vect.end()){
        std::cout << *iter << ", ";
        iter++;
    }
    std::cout << "\n";
}
int main(){
    int polling = 1;
    vector<POINT> locations;
    vector<int> delays;
    vector<int> clickDurations;
    screen screen((double)GetSystemMetrics(SM_CXSCREEN),
                  (double)GetSystemMetrics(SM_CYSCREEN));
    std::atomic_bool stop = false;
    thread stopThread(stopProgram, ref(stop));
    thread recordClick(recordClicks, ref(stop), ref(delays), ref(clickDurations));
    thread recordMovement(continuousRecord, ref(stop), ref(locations), ref(polling));
    system("cls");
    setCursor(false);
    POINT p;
    while(!stop){
        GetCursorPos(&p);
        cout << p.x << ", " << p.y << "             \n";
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


    for(long long unsigned int i = 0; i < clickDurations.size(); i++){
        cout << "\nsleeping for " << delays[i] << "ms\n";
        Sleep(delays[i]);
        cout << "\nclicking down for " << clickDurations[i] << "ms\n";
        Sleep(clickDurations[i]);
    }
    
    exit(0);



    for(auto iter = locations.begin(); iter != locations.end(); iter++){
        moveToPoint(*iter, screen);
        std::this_thread::sleep_for(std::chrono::milliseconds(polling));
    }
    exit(0);

}

void stopProgram(std::atomic_bool& stop){
    while(1){
        if((GetKeyState(VK_MENU) & 0x8000) && (GetKeyState(0x51) & 0x8000)){
            stop = true;
            return;
        }
    }
}
