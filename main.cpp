/*References
get cursor pos  https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getcursorpos
POINT           https://learn.microsoft.com/en-us/previous-versions/dd162805(v=vs.85)
get key state   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getkeystate
mouse input     https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-mouseinput
INPUT           https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-input
send input      https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput
MOUSEINPUT      https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-mouseinput
key codes       https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

TODO:
load/save backup
json saved macros
keyboard support
multiple monitor support
*/

#include <windows.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <vector>

#include "display.h"
#include "screen.h"
#include "mouse.h"
#include "menu.h"
#include "json.hpp"

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::ref;

int main(){
    string filename;
    nlohmann::ordered_json savedMacros;
    std::ifstream load("profile.json");
    if(load){
        savedMacros = nlohmann::ordered_json::parse(load);
        saveToFile("backup.json", savedMacros);
    }
    load.close();
    screen screen;
    string input;
    while(1){
        system("cls");
        cout << "1. Run saved macro\n"
             << "2. Record new macro\n"
             << "3. View macros\n"
             << "4. Edit macro click duration\n"
             << "5. Delete macro\n"
             << "6. Load profile\n"
             << "7. Save profile\n"
             << "\n\nq to quit\n\n";
        cin >> input;
        system("cls");
        if(input == "1"){
            if(printSavedTargets(savedMacros)){
                continue;
            }
            string name = chooseFromSaved(savedMacros);
            vector<int> delays = savedMacros[name]["delays"];
            vector<int> clickDurations = savedMacros[name]["clickDurations"];
            vector<POINT> locations(savedMacros[name]["locations"].size());
            system("cls");
            cout << "Running...\n\n";
            int i = 0;
            for(auto iter : savedMacros[name]["locations"]){
                locations[i].x = iter[0];
                locations[i].y = iter[1];
                i++;
            }
            thread mouseMovement(runMovement, ref(locations), ref(screen));
            runClicks(clickDurations, delays);
            mouseMovement.join();
            system("cls");
            system("pause");
        }else if(input == "2"){
            string name;
            cout << "Enter macro name: ";
            cin >> name;
            savedMacros[name] = recordMouse();
            saveToFile("profile.json", savedMacros);
        }else if(input == "3"){
            if(printSavedTargets(savedMacros)){
                continue;
            }
            system("pause");
            continue;
        }else if(input == "4"){
            if(printSavedTargets(savedMacros)){
                continue;
            }
            string name = chooseFromSaved(savedMacros);
            string prompt = "Enter new keypress duration: ";
            int duration = getIntInput(prompt);
            for(unsigned long long int i = 0; i < savedMacros[name]["clickDurations"].size(); i++){
                savedMacros[name]["clickDurations"][i] = duration;
            }
            saveToFile("profile.json", savedMacros);
        }else if(input == "5"){
            if(printSavedTargets(savedMacros)){
                continue;
            }
            savedMacros.erase(chooseFromSaved(savedMacros));
            saveToFile("profile.json", savedMacros);
        }else if(input == "6"){
            cout << "Enter filename: ";
            cin >> filename;
            std::ifstream load(filename);
            if(load){
                savedMacros = nlohmann::ordered_json::parse(load);
            }else{
                system("cls");
                cout << "File does not exist\n\n";
                system("pause");
            }
            load.close();
        }else if(input == "7"){
            cout << "Enter filename: ";
            cin >> filename;
            std::ofstream createBackup(filename);
            createBackup << savedMacros.dump(1) + "\n";
            createBackup.close();
        }else if(input == "q"){
            break;
        }
    }
    system("cls");
    return 0;
}
