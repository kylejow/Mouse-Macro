/*https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getcursorpos?redirectedfrom=MSDN
https://learn.microsoft.com/en-us/previous-versions/dd162805(v=vs.85)
https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-screentoclient?redirectedfrom=MSDN
https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getkeystate
*/

#include <windows.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

using std::cout;
using std::cin;
using std::thread;
using std::vector;

void stopProgram(std::atomic_bool& stop){
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    cin.get();
    stop = true;
    return;
}

void setCursor(bool visible){
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void clearScreen(){
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void addLocations(std::atomic_bool& stop, vector<POINT>& locations){
    POINT pos;
    while(!stop){
        if((GetKeyState(VK_LBUTTON) & 0x80) != 0){
            GetCursorPos(&pos);
            locations.push_back(pos);
            while((GetKeyState(VK_LBUTTON) & 0x80) != 0){};
        }
    }
    return;
}

void printPOINT(POINT& p){
    cout << p.x << ", " << p.y;
}

int main(){
    vector<POINT> locations;
    std::atomic_bool stop = false;
    thread stopThread(stopProgram, ref(stop));
    //thread recordClicks(addLocations, ref(stop), ref(locations));
    system("cls");
    setCursor(false);
    POINT p;
    while (!stop){
        GetCursorPos(&p);
        cout << p.x << ", " << p.y << "             \n";
        cout << locations.size();
        clearScreen();
    }
    cout << "enter to stop\n";
    stopThread.join();
    //recordClicks.join();
    setCursor(true);
    for(auto iter = locations.begin(); iter != locations.end(); iter++){
        printPOINT(*iter);
        cout << "\n";
    }
    system("pause");
}