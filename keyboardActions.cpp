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
    GetKeyboardState(lpKeyState);
    while(!lpKeyState[65]){
        GetKeyboardState(lpKeyState);
    }
}