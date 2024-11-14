#ifndef ENTITY_H
#define ENTITY_H

#include "Maze.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Entity {
public:
    Entity();
    Entity(const std::string& name, Room* location);
    Entity(const std::string& name,Room* location,int health,int level);
    Entity(const string& name, Room* location, int health, int level, int mp, int atk, int def, int cr, int cd);
    virtual ~Entity() = default;


    virtual void useSkill(int skillIndex);
    virtual void printStatus() const;

    // Getters
    const string &getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    const map<string, bool> &getStatuses() const;
    int getMP() const;
    int getAtk() const;
    int getDef() const;
    int getCr() const;
    int getCd() const;

    // Setters
    void setHealth(int newHealth);
    void subtractHealth(int lostHealth);
    void applyStatus(const string &status);
    void removeStatus(const string &status);
    void setMP(int newMP);
    
protected:
    string name;
    int health;
    int maxHealth;
    int mp;
    int atk;
    int def;
    int cr; // Critical hit chance
    int cd; // Cooldown reduction
    bool isAlive;
    Room* location;
    map<string, bool> statuses;

private:
    void levelUpStats();
};

class Player : public Entity {
public:
    void moveTo(Room *room);
    void moveN();
    void moveE();
    void moveS();
    void moveW();
    void moveP();
    Player(const string& name, Room* location);
    int getExperience() const;
    int getLevel() const;
    const vector<Item> &getInventory() const;
    void addExperience(int exp);
    void addToInventory(Item item);
    void removeFromInventory(Item item);
    void levelUp();
    virtual void useSkill(int skillIndex) override;

protected:
    int experience;
    int level;
    vector<Item> inventory;
};

class Knight : public Player {
public:
    Knight(Room* location);
    void useSkill(int skillIndex) override;
};

class Mage : public Player {
public:
    Mage(Room* location);
    void useSkill(int skillIndex) override;
};

class Rogue : public Player {
public:
    Rogue(Room* location);
    void useSkill(int skillIndex) override;
};

class Barbarian : public Player {
public:
    Barbarian(Room* location);
    void useSkill(int skillIndex) override;
};

// Monsters

class Slime : public Entity {
public:
    Slime(Room* location);
};

class Goblin : public Entity {
public:
    Goblin(Room* location);
};

class Bird : public Entity {
public:
    Bird(Room* location);
};

#endif // ENTITY_H