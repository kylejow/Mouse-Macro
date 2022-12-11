//https://en.cppreference.com/w/cpp/thread/sleep_for

#include "mouse.h"
#include "cputimer.h"

void pointToABSInput(MOUSEINPUT& mi, POINT& p, screen& screen){
    double ABS = 65535.0;
    mi.dx = ((double)p.x/screen.getXLen())*ABS;
    mi.dy = ((double)p.y/screen.getYLen())*ABS;
    mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
    // return mi; black screen when returning MOUSINPUT?
}

POINT absInputToPoint(MOUSEINPUT& mi, screen& screen){
    POINT p;
    double ABS = 65535.0;
    p.x = ((LONG)mi.dx*screen.getXLen())/ABS;
    p.y = ((LONG)mi.dy*screen.getYLen())/ABS;
    return p;
}

void recordMovements(std::atomic_bool& stop, vector<POINT>& locations, int& polling){
    POINT pos;
    while(!stop){
        GetCursorPos(&pos);
        locations.push_back(pos);
        std::this_thread::sleep_for(std::chrono::milliseconds(polling));
    }
    return;
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

void moveToPoint(POINT& p, screen& screen){
    INPUT move[1] = {0};
    move[0].type = INPUT_MOUSE;
    pointToABSInput(move[0].mi, p, screen);
    SendInput(1, move, sizeof(INPUT));
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

nlohmann::ordered_json recordMouse(int& polling){
    vector<int> delays;
    vector<int> clickDurations;
    vector<POINT> locations;
    system("cls");
    cout << "Press shift to start recording\n";
    while(!(GetKeyState(VK_SHIFT) & 0x8000)){};

    std::atomic_bool stop = false;
    thread stopThread(stopProgram, ref(stop));
    thread recordClick(recordClicks, ref(stop), ref(delays), ref(clickDurations));
    thread recordMovement(recordMovements, ref(stop), ref(locations), std::ref(polling));
    system("cls");
    setCursor(false);
    POINT p;
    while(!stop){
        GetCursorPos(&p);
        cout << "Current Location: " << p.x << ", " << p.y << "             \n";
        cout << "\n\nPress esc to stop recording\n";
        clearScreen();
    }
    stopThread.join();
    recordClick.join();
    recordMovement.join();
    setCursor(true);
    nlohmann::ordered_json macro;
    macro["delays"] = delays;
    macro["clickDurations"] = clickDurations;
    vector<long> tmp = {NULL, NULL};
    for(unsigned long long int i = 0; i < locations.size(); i++){
        tmp[0] = locations[i].x;
        tmp[1] = locations[i].y;
        macro["locations"][i] = tmp;
    }
    system("cls");
    return macro;
}


void runMovement(vector<POINT>& locations, screen& screen, int& polling){
    for(auto iter = locations.begin(); iter != locations.end(); iter++){
        moveToPoint(*iter, screen);
        std::this_thread::sleep_for(std::chrono::milliseconds(polling));
    }
}

void runClicks(vector<int>& clickDurations, vector<int>& delays){
    int length = clickDurations.size();
    for(int i = 0; i < length; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(delays[i]));
        click(clickDurations[i]);
    }
}
