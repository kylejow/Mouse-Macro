#include <windows.h>
#include <iostream>

int main(){
    PBYTE lpKeyState;
    GetKeyboardState(lpKeyState);
    std::cout << lpKeyState[0];
}