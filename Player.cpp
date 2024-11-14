#include "Entity.h"

Player::Player(const string& name, Room* location) : Entity(name, location, 100, 1, 50, 10, 5, 5, 150) {}

void Player::moveTo(Room* room) {
    if (room) {
        location = room;
        cout << name << " moved to " << room->type() << ".\n";
    } else {
        cout << "Invalid room.\n";
    }
}
void Player::moveN(){
    Player::moveTo(location->connections[N]);
}
void Player::moveE(){
    Player::moveTo(location->connections[E]);
}
void Player::moveS(){
    Player::moveTo(location->connections[S]);
}
void Player::moveW(){
    Player::moveTo(location->connections[W]);
}
void Player::moveP(){
    Player::moveTo(location->connections[P]);
}

int Player::getExperience() const { return experience; }
int Player::getLevel() const { return level; }
const vector<Item>& Player::getInventory() const { return inventory; }
void Player::addExperience(int exp) {
    experience += exp;
    levelUp();
}

void Player::addToInventory(Item item) {
    inventory.push_back(item);
}

void Player::removeFromInventory(Item item) {
    inventory.erase(remove(inventory.begin(), inventory.end(), item), inventory.end());
}
void Player::levelUp() {
    const int expToLevelUp = 100; 
    while (experience >= expToLevelUp) {
        experience -= expToLevelUp;
        level++;
        maxHealth += 10;
        health = maxHealth;
        cout << name << " leveled up to level " << level << "!\n";
    }
}

void Player::useSkill(int skillIndex) {
    // Override with specific player skills
}

// Knight
Knight::Knight(Room* location) : Player("Knight", location) {
    health = 150;
    atk = 10;
    def = 15;
    mp = 30;
}

void Knight::useSkill(int skillIndex) {
    // Implement Knight skills here
}

// Mage
Mage::Mage(Room* location) : Player("Mage", location) {
    health = 80;
    atk = 5;
    def = 5;
    mp = 100;
}

void Mage::useSkill(int skillIndex) {
    // Implement Mage skills here
}

// Rogue
Rogue::Rogue(Room* location) : Player("Rogue", location) {
    health = 100;
    atk = 12;
    def = 8;
    mp = 50;
}

void Rogue::useSkill(int skillIndex) {
    // Implement Rogue skills here
}

// Barbarian
Barbarian::Barbarian(Room* location) : Player("Barbarian", location) {
    health = 130;
    atk = 18;
    def = 8;
    mp = 20;
}

void Barbarian::useSkill(int skillIndex) {
    // Implement Barbarian skills here
}
