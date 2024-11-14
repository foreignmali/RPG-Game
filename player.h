#ifndef PLAYER_H
#define PLAYER_H

#include "maze.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Item {
public:
    virtual string type() const;
    bool operator==(const Item& other) const { return type() == other.type(); }
};

class Player {
public:
Player(const std::string& name, Room* startingRoom);
    
    void moveTo(Room* room);
    void moveN();
    void moveE();
    void moveS();
    void moveW();
    
    // Getters
    const string& getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getExperience() const;
    int getLevel() const;
    const vector<Item>& getInventory() const;
    const map<string, bool>& getStatuses() const;

    // Setters
    void setHealth(int newHealth);
    void subtractHealth(int lostHealth);
    void addExperience(int exp);
    void addToInventory(Item item);
    void removeFromInventory(Item item);
    void applyStatus(const string& status);
    void removeStatus(const string& status);
    void printStatus() const;
    Room* getCurrentRoom() const;

private:
    string name;
    int health;
    int maxHealth;
    int experience;
    int level;
    bool isAlive;
    Room* currentRoom;
    vector<Item> inventory;
    map<string, bool> statuses;

    void levelUp();
};

#endif // PLAYER_H
