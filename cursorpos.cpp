/*https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getcursorpos?redirectedfrom=MSDN
https://learn.microsoft.com/en-us/previous-versions/dd162805(v=vs.85)
https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-screentoclient?redirectedfrom=MSDN
https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getkeystate
https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
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

class screen{
    public:
        screen(double x, double y);
        double getXLen(void);
        double getYLen(void);
    private:
        const double xLen;
        const double yLen;
};

screen::screen(double x, double y) : xLen(x), yLen(y){}
double screen::getXLen(void){return xLen;}
double screen::getYLen(void){return yLen;}

void stopProgram(std::atomic_bool& stop){
    while(1){
        if((GetKeyState(VK_MENU) & 0x8000) && (GetKeyState(0x51) & 0x8000)){
            stop = true;
            return;
        }
    }
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

void pointToABSInput(MOUSEINPUT& mi, POINT& p, screen& screen){
    double ABS = 65535.0;
    int x = ((double)p.x/screen.getXLen())*ABS;
    int y = ((double)p.y/screen.getYLen())*ABS;
    mi.dx = x;
    mi.dy = y;
    mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
    // return mi; black screen when returning MOUSINPUT?
}

void clickPoint(POINT& p, screen& screen){
    int numInputs = 1;
    INPUT Inputs[numInputs] = {0};
    Inputs[0].type = INPUT_MOUSE;
    pointToABSInput(Inputs[0].mi, p, screen);
    SendInput(1, Inputs, sizeof(INPUT));
}

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
        cout << "\n";
    }
    system("pause");
    for(auto iter = locations.begin(); iter != locations.end(); iter++){
        clickPoint(*iter, screen);
        Sleep(1000);
    }
}