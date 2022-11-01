#include "menu.h"

void printSavedTargets(nlohmann::ordered_json& savedMacros){
    int i = 1;
    for(auto macro : savedMacros){
        cout << i++ << ". " << macro["Name"].get<std::string>() << "\n";
    }
    cout << "\n";
}

bool noSavedMacros(nlohmann::ordered_json& savedMacros){
    if(savedMacros.size() == 0){
        system("cls");
        cout << "No saved macros\n\n\n";
        system("pause");
        return true;
    }
    return false;
}

int chooseFromSaved(nlohmann::ordered_json savedMacros){
    int chosen = 0;
    int numSaved = savedMacros.size();

    system("cls");
    printSavedTargets(savedMacros);
    cin >> chosen;
    while(cin.fail() || chosen < 1 || chosen > numSaved){
        system("cls");
        printSavedTargets(savedMacros);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        cin >> chosen;
    }
    return chosen;
}