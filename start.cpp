#include <iostream>
#include <string>
#include <iomanip>
#include <maze.h>
#include <player.h>

using namespace std;

int getChoice(){
    int choice;

    cout << "\n\t==========================\n";
    cout << "\t         Start Menu \n";
    cout << "\t==========================\n";
    cout << "\t 1. New Game\n";
    cout << "\t 2. Load Game\n";
    cout << "\t 3. Exit\n";
    cout << "\t==========================\n";
    cout << "\t Enter your choice (1-3): ";
    cin >> choice;
    cout << "\n";
    return choice;

}

void displayStats (const string& name, const string& archetypeName, int health, int power ){
    cout << "\n\t==========================\n";
    cout << "\t     Character Stats \n";
    cout << "\t==========================\n";
    cout << "\t Name: " << name << endl;
    cout << "\t Archetype: " << archetypeName << endl;
    cout << "\t Health: " << health << endl;
    cout << "\t Power: " << power << endl;
    cout << "\t==========================\n";


}
int main(){

    int choice;


    do {
        
        choice = getChoice();

     
        if (choice == 1) {
    
            string name;
            int archetype;
            cout << "\t What is your name? ";
            cin >> name;
            cout << "\t What is your fighter archetype? " << endl;
            cout << "\t 1. Knight" << endl;
            cout << "\t 2. Mage" << endl;
            cout << "\t 3. Assassin" << endl;
            cin >> archetype;

            string archetypeName;
            int health, power;
            switch(archetype) {

                case 1:
                    archetypeName = "Knight";
                    cout << "\t You have chosen to be a Knight.";
                    health = 200;
                    power = 50;
                    break;
                case 2:
                    archetypeName = "Mage";
                    cout << "\t You have chosen to be a Mage.";
                    health = 50;
                    power = 200;
                    break;
                case 3:
                    archetypeName = "Assassin";
                    cout << "\t You have chosen to be an Assassin." << endl;
                    health = 100;
                    power = 100;
                    break;
                default:
                    cout << "\t Invalid Input!";
                    break;
            }
            if (archetype >= 1 && archetype <= 3){
                displayStats(name, archetypeName, health, power);
            }
        } else if (choice == 2){
            cout << "\nLoading game..." << endl;
        } else if (choice == 3){
            cout << "\nExiting game." << endl;
        } else {
            cout << "\nInvalid input! 1-3.";
        }


    } while (choice != 3);


    return 0;
}

