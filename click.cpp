#include <windows.h>
//https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput?redirectedfrom=MSDN
//https://stackoverflow.com/questions/28386029/how-to-simulate-mouse-click-using-c
/*https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput
https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-mouseinput

*/

int main(){
    int numInputs = 1;
    INPUT Inputs[numInputs] = {0};

    LONG x = 632;
    LONG y = 305;

    Inputs[0].type = INPUT_MOUSE;
    Inputs[0].mi.dx = (x/1920.0)*65535.0; // desired X coordinate
    Inputs[0].mi.dy = (y/1080.0)*65535.0; // desired Y coordinate
    Inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;

    // Inputs[1].type = INPUT_MOUSE;
    // Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    // Inputs[2].type = INPUT_MOUSE;
    // Inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(1, Inputs, sizeof(INPUT));
}