#include "display.h"

#include <iostream>

int display::initialDisplay(vector<pair<string, int>> institutes)
{
    string choice;
    int returnable;
    cout << "Choose a ranked institution" << endl;
    for(int i = 1; i <= 25; i++)
    {
        cout << i << ". " << institutes[i-1].first << ", Score: " << institutes[i-1].second << endl;
    }
    try{
        cin >> choice;
        returnable = stoi(choice);
        if(returnable < 1 || returnable > 25)
            throw 1;
    }
    catch(...)
    {
        cerr << "You must give a valid choice" << endl;
        return -1;
    }
    return returnable - 1;
}
//int chooseGroup(vector<pair<string, int>> groups)
//{}