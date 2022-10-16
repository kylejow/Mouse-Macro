#include "mouse.h"
#include "cputimer.h"
#include <iostream>
void addLocations(std::atomic_bool& stop, vector<POINT>& locations, vector<double>& delays){
    POINT pos;
    cputimer cputimer;
    cputimer.reset();
    while(!stop){
        if((GetKeyState(VK_LBUTTON) & 0x80) != 0){
            cputimer.stop();
            delays.push_back(cputimer.elapsed());
            cputimer.reset();
            GetCursorPos(&pos);
            locations.push_back(pos);
            while((GetKeyState(VK_LBUTTON) & 0x80) != 0){};
        }
    }
    return;
}

void pointToABSInput(MOUSEINPUT& mi, POINT& p, screen& screen){
    double ABS = 65535.0;
    mi.dx = ((double)p.x/screen.getXLen())*ABS;
    mi.dy = ((double)p.y/screen.getYLen())*ABS;
    mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
    // return mi; black screen when returning MOUSINPUT?
}

void clickPoint(POINT& p, screen& screen){
    INPUT Inputs[3] = {0};
    Inputs[0].type = INPUT_MOUSE;
    pointToABSInput(Inputs[0].mi, p, screen);
    Inputs[1].type = INPUT_MOUSE;
    Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    Inputs[2].type = INPUT_MOUSE;
    Inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(3, Inputs, sizeof(INPUT));
}