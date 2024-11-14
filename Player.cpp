#include "player.h"

// Item 
string Item::type() const {
    return "Item";
}

// Player
Player::Player(const std::string& name, Room* startingRoom): name(name), currentRoom(startingRoom), health(100), maxHealth(100), experience(0), level(1), isAlive(true) {}

// Movement
void Player::moveTo(Room* room) {
    if (room) {
        currentRoom = room;
        cout << name << " moved to " << room->type() << ".\n";
    } else {
        cout << "Invalid room.\n";
    }
}
void Player::moveN(){
    Player::moveTo(currentRoom->connections[N]);
}
void Player::moveE(){
    Player::moveTo(currentRoom->connections[E]);
}
void Player::moveS(){
    Player::moveTo(currentRoom->connections[S]);
}
void Player::moveW(){
    Player::moveTo(currentRoom->connections[W]);
}


// Getters
const string& Player::getName() const { return name; }
int Player::getHealth() const { return health; }
int Player::getMaxHealth() const { return maxHealth; }
int Player::getExperience() const { return experience; }
int Player::getLevel() const { return level; }
const vector<Item>& Player::getInventory() const { return inventory; }
const map<string, bool>& Player::getStatuses() const { return statuses; }

// Setters
void Player::setHealth(int newHealth) {
    health = max(0, min(newHealth, maxHealth)); // [0, maxHealth]
    if (health == 0) {
        isAlive = false; // Player is dead if health drops to 0
    }
}

void Player::subtractHealth(int lostHealth) {
    setHealth(health - lostHealth);
}

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

void Player::applyStatus(const string& status) {
    statuses[status] = true;
}

void Player::removeStatus(const string& status) {
    statuses.erase(status);
}

void Player::printStatus() const {
    cout << "Player: " << name << "\n";
    cout << "Health: " << health << "/" << maxHealth << "\n";
    cout << "Level: " << level << "\n";
    cout << "Experience: " << experience << "\n";
    cout << "Inventory: ";
    for (Item item : inventory) {
        cout << item.type() << " ";
    }
    cout << "\nStatuses: ";
    for (const auto& status : statuses) {
        cout << status.first << (status.second ? " (active) " : " (inactive) ");
    }
    cout << "\n";
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

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

int main(){
    Maze maze(5, 5);
    Room* spawnRoom = maze.getSpawnRoom();

    if(!spawnRoom){
        cout<<"Could not find spawn room\n";
        return 1;
    }

    string name;
    string input;
    cout<<"Input player name:\n";
    cin >> name;
    Player player("hero", spawnRoom);
    player.printStatus();

    while(true){

        cout<<maze.toString(player.getCurrentRoom());

        cout<<"Enter direction (N, E, S, W) to move: ";
        cin >> input;
        if (input == "N" || input == "n") {
            player.moveN();
        } else if (input == "E" || input == "e") {
            player.moveE();
        } else if (input == "S" || input == "s") {
            player.moveS();
        } else if (input == "W" || input == "w") {
            player.moveW();
        } else {
            cout << "Invalid direction. Please enter N, E, S, or W.\n";
            continue;
        }
        if (player.getCurrentRoom()->type() == "Boss Room") {
            cout << "Congratulations! You've reached the Boss Room and won the game!\n";
            break;
        }
        player.printStatus();
    }

    return 0;
    
}