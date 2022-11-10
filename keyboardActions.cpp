#include <windows.h>
#include <iostream>

int main(){
    BYTE lpKeyState[256];
    // Sleep(2000);
    // if(GetKeyboardState(lpKeyState)){
    //     for(int i = 0; i < 256; i++){
    //         std::cout << lpKeyState[i] << ", ";
    //     }
    //     std::cout << "\n";
    //     std::cout << lpKeyState[65];
    // }
    Sleep(2000);
    if(GetKeyboardState(lpKeyState)){
        std::cout << "success\n";
        if((lpKeyState[16] & 0x8000) != 0){
            std::cout << "shift down from kbstate";
        }
    }
    if((GetKeyState(16) & 0x8000) != 0){
        std::cout << "shift down from getkeystate";
    }

}