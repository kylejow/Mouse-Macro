//https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getcursorpos?redirectedfrom=MSDN

#include <windows.h>
#include <iostream>
#include <thread>
#include <atomic>

using std::cout;
using std::cin;
using std::thread;

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

int main(){
    POINT pos;
    std::atomic_bool stop = false;
    thread stopThread(stopProgram, ref(stop));
    system("cls");
    setCursor(false);
    while (!stop){
        GetCursorPos(&pos);
        cout << pos.x << ", " << pos.y << "              ";
        clearScreen();
    }
    stopThread.join();
    setCursor(true);
}