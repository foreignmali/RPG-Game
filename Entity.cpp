#include "Entity.h"

// Entity
Entity::Entity():health(0), maxHealth(0), isAlive(false) {}
Entity::Entity(const std::string& name, Room* location): name(name), location(location), health(100), maxHealth(100), isAlive(true) {}
Entity::Entity(const std::string& name,Room* location,int health,int level):location(location), health(health), maxHealth(health), isAlive(true) {}
Entity::Entity(const string &name, Room *location, int health, int level, int mp, int atk, int def, int cr, int cd){}

// Movement

// Getters
const string& Entity::getName() const { return name; }
int Entity::getHealth() const { return health; }
int Entity::getMaxHealth() const { return maxHealth; }
const map<string, bool>& Entity::getStatuses() const { return statuses; }

// Setters
void Entity::setHealth(int newHealth) {
    health = max(0, min(newHealth, maxHealth)); // [0, maxHealth]
    if (health == 0) {
        isAlive = false; // Entity is dead if health drops to 0
    }
}

void Entity::subtractHealth(int lostHealth) {
    setHealth(health - lostHealth);
}


void Entity::applyStatus(const string& status) {
    statuses[status] = true;
}

void Entity::removeStatus(const string& status) {
    statuses.erase(status);
}



