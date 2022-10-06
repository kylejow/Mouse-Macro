/*https://vcpptips.wordpress.com/tag/vk_lbutton/
*/

#include <windows.h>
#include <iostream>
#include <thread>
#include <atomic>

using std::cout;
using std::cin;
using std::thread;

void monitorClick(std::atomic_bool& stop){
    while(1){
        if((GetKeyState(VK_LBUTTON) & 0x80) != 0){
            cout << "click";
            stop = true;
            return;
        }
    }
}

int main(){

    std::atomic_bool stop = false;
    thread lClick(monitorClick, ref(stop));
    int i = 0;
    while(!stop){
        cout << i++;
        system("clear");
    }
    lClick.join();
}


