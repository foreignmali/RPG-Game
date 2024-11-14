#include "Consumables.h"
#include <iostream>

std::string Item::getType() const {
    return "Generic Item";
}

// Weapon-specific implementation
std::string Weapon::getType() const {
    return "Weapon";
}

void Weapon::use() {
    std::cout << "You swing the weapon!" << std::endl;
}

// Potion-specific implementation
std::string Potion::getType() const {
    return "Potion";
}

void Potion::use() {
    std::cout << "You drink the potion!" << std::endl;
}

// Armor-specific implementation
std::string Armor::getType() const {
    return "Armor";
}

void Armor::use() {
    std::cout << "You equip the armor!" << std::endl;
}