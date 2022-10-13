#include <windows.h>
#include <iostream>
//https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput?redirectedfrom=MSDN
//https://stackoverflow.com/questions/28386029/how-to-simulate-mouse-click-using-c
/*https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput
https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-mouseinput

*/

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
    screen screen((double)GetSystemMetrics(SM_CXSCREEN),
                  (double)GetSystemMetrics(SM_CYSCREEN));

    int numInputs = 1;
    INPUT Inputs[numInputs] = {0};

    POINT p;
    p.x = 632;
    p.y = 305;

    Inputs[0].type = INPUT_MOUSE;
    pointToABSInput(Inputs[0].mi, p, screen);
    // Inputs[1].type = INPUT_MOUSE;
    // Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    // Inputs[2].type = INPUT_MOUSE;
    // Inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(1, Inputs, sizeof(INPUT));
}
