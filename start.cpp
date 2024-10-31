#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main(){

int choice; 


do {
    cout << "\t Start Menu" << endl;
    cout << "1. New Game " << endl;
    cout << "2. Load Game " << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

     
    if (choice == 1) {
    
    string name;
    int archetype;
    cout << "\t What is your name? ";
    cin >> name;
    cout << "\t What is your fighter archetype? ";
    cout << "1. Knight" << endl;
    cout << "2. Mage" << endl;
    cout << "3. Assassin" << endl;
    cin >> archetype;
    
    int health, power;
    if (archetype == 1){
        cout << "You have chosen to be a Knight.";
        health = 200;
        power = 50;
    } else if (archetype == 2){
        cout << "You have chosen to be a Mage.";
        health = 50;
        power = 200;

   } else if (archetype == 3){
        cout << "You have chosen to be an Assasin.";
        health = 100;
        power = 100;
   } 

   cout << "\t Character Stats" << endl;
   cout << "Name: " << name;
   cout << "Archetype: " << archetype << endl;
   cout << "Health: " << health << endl;
   cout << "Power: " << power << endl;


} else if (choice == 2){
    cout << "Loading game..." << endl;
} else if (choice >= 3){
    cout << "Exiting game." << endl;
} else {
    cout << "Invalid input! 1-3.";
}

} while (choice != 3);


    return 0;
}