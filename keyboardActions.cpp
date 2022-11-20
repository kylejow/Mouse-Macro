//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

#include <windows.h>
#include <iostream>
#include <vector>
using std::vector;
using std::cout;

vector<bool> keysDown(void){
    vector<bool> keys(256);
    for(int i = 0; i < 256; i++){
        keys[i] = (bool)(GetKeyState(i) & 0x8000);
    }
    return keys;
}
int main(){
    // Sleep(2000);
    // if(GetKeyboardState(lpKeyState)){
    //     for(int i = 0; i < 256; i++){
    //         std::cout << lpKeyState[i] << ", ";
    //     }
    //     std::cout << "\n";
    //     std::cout << lpKeyState[65];
    // }
    Sleep(2000);
    vector<bool> keys = keysDown();
    if(keys[0x38]){
        cout << "8 down";
    }
}