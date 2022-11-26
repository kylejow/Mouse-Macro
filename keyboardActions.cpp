//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

#include <windows.h>
#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>

#include "program.h"

using std::vector;
using std::cout;
using std::thread;
using std::ref;

vector<bool> keysDown(void){
    vector<bool> keys(256);
    for(int i = 0; i < 256; i++){
        keys[i] = (bool)(GetKeyState(i) & 0x8000);
    }
    return keys;
}
void recordKeyboard(std::atomic_bool& stop, vector<vector<bool>>& keys){
    while(!stop){
        vector<bool> ajsnfanjk = keysDown();
        keys.push_back(ajsnfanjk);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return;
}
void keyPress(int duration, int key){
    INPUT down[1] = {0};
    down[0].type = INPUT_KEYBOARD;
    down[0].ki.wVk= key;
    SendInput(1, down, sizeof(INPUT));
    //std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    INPUT up[1] = {0};
    up[0].type = INPUT_KEYBOARD;
    up[0].ki.wVk= key;
    up[0].mi.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, up, sizeof(INPUT));
}
void runKeyboard(vector<vector<bool>>& keys){
    vector<bool> prev(256, false);
    for(auto iter = keys.begin(); iter != keys.end(); iter++){
        for(int i = 0; i < 256; i++){
            if((*iter)[i] == true && prev[i] == false){
                prev[i] == true;
                keyPress(1, i);
            }
            if((*iter)[i] == false && prev[i] == true){
                prev[i] == false;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main(){
    system("cls");
    cout << "\nPress shift to start recording\n";
    while(!(GetKeyState(VK_SHIFT) & 0x8000)){};
    system("cls");
    cout << "\nalt q to stop\n";
    std::atomic_bool stop = false;
    vector<vector<bool>> keys;
    thread stopThread(stopProgram, ref(stop));
    thread keyboard(recordKeyboard, ref(stop), ref(keys));
    keyboard.join();
    stopThread.join();
    system("cls");
    cout << "\nPress shift to run\n";
    while(!(GetKeyState(VK_SHIFT) & 0x8000)){};
    runKeyboard(keys);
}