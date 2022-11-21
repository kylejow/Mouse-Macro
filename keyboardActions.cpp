//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

#include <windows.h>
#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>

using std::vector;
using std::cout;

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
void runKeyboard(vector<vector<bool>>& keys){
    vector<bool> prev(256, false);
    for(auto iter = keys.begin(); iter != keys.end(); iter++){
        for(auto iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++){

        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
int main(){
    Sleep(2000);
    vector<bool> keys = keysDown();
    if(keys[0x38]){
        cout << "8 down";
    }
}