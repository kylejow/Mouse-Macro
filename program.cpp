#include "program.h"

void stopProgram(std::atomic_bool& stop){
    while(1){
        if((GetKeyState(VK_MENU) & 0x8000) && (GetKeyState(0x51) & 0x8000)){
            stop = true;
            return;
        }
    }
}