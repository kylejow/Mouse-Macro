#include "menu.h"

void printSavedTargets(nlohmann::ordered_json& savedMacros){
    int num = 1;
    for(auto i = savedMacros.begin(); i != savedMacros.end(); i++){
        cout << num++ << ". " << i.key() << "\n";
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

string chooseFromSaved(nlohmann::ordered_json savedMacros){
    int chosen = 0;
    int numSaved = savedMacros.size();
    vector<string> names;
    for(auto i = savedMacros.begin(); i != savedMacros.end(); i++){
        names.push_back(i.key());
    }
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
    return names[chosen-1];
}