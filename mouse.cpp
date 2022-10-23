//https://en.cppreference.com/w/cpp/thread/sleep_for

#include "mouse.h"
#include "cputimer.h"

void addLocations(std::atomic_bool& stop, vector<POINT>& locations, vector<double>& delays, vector<double>& clickDurations){
    POINT pos;
    cputimer delay;
    cputimer duration;
    delay.reset();
    while(!stop){
        if((GetKeyState(VK_LBUTTON) & 0x80) != 0){
            duration.reset();
            delay.stop();
            delays.push_back(delay.elapsed());
            delay.reset();
            GetCursorPos(&pos);
            locations.push_back(pos);
            while((GetKeyState(VK_LBUTTON) & 0x80) != 0){};
            duration.stop();
            clickDurations.push_back(duration.elapsed());
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

void clickPoint(POINT& p, screen& screen, double& duration){
    INPUT moveClick[2] = {0};
    moveClick[0].type = INPUT_MOUSE;
    pointToABSInput(moveClick[0].mi, p, screen);
    moveClick[1].type = INPUT_MOUSE;
    moveClick[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(2, moveClick, sizeof(INPUT));
    Sleep(duration);
    INPUT release[1] = {0};
    release[0].type = INPUT_MOUSE;
    release[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, release, sizeof(INPUT));
}

void continuousRecord(std::atomic_bool& stop, vector<POINT>& locations, int& polling){
    POINT pos;
    while(!stop){
        GetCursorPos(&pos);
        locations.push_back(pos);
        std::this_thread::sleep_for(std::chrono::milliseconds(polling));
    }
    return;
}

void moveToPoint(POINT& p, screen& screen){
    INPUT move[1] = {0};
    move[0].type = INPUT_MOUSE;
    pointToABSInput(move[0].mi, p, screen);
    SendInput(1, move, sizeof(INPUT));
}

void recordClicks(std::atomic_bool& stop, vector<int>& delays, vector<int>& clickDurations){
    cputimer delay;
    cputimer clickDuration;
    delay.reset();
    while(!stop){
        if((GetKeyState(VK_LBUTTON) & 0x80) != 0){
            delay.stop();
            delays.push_back(delay.elapsed());
            clickDuration.reset();
            while((GetKeyState(VK_LBUTTON) & 0x80) != 0){};
            clickDuration.stop();
            clickDurations.push_back(clickDuration.elapsed());
            delay.reset();
        }
    }
    return;
}

void click(int& duration){
    INPUT down[1] = {0};
    down[0].type = INPUT_MOUSE;
    down[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, down, sizeof(INPUT));
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    INPUT up[1] = {0};
    up[0].type = INPUT_MOUSE;
    up[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, up, sizeof(INPUT));
}