#include "Maze.h"

Room::Room(){}
Room::Room(int x, int y) : coordinates({x,y}) {}

void Room::init(){}

void Room::connect(Direction direction, Room* room) {
    connections[direction] = room;
    room->connections[(direction + 2) % 4 ] = this; // Connect back in the opposite direction
}
void Room::makePortal(Room* room){
    connections[P]=room;
    room->connections[P] = this;
}
void Room::clearPortal(){
    connections[P]=nullptr;
}

int Room::connectionCount() {
    int out = 0;
    for (auto c : connections) {
        if (c != nullptr) out++;
    }
    return out;
}

bool Room::isConnected() {
    return connected;
}

string Room::type() {
    return "Empty Room";
}

// Derived room types 
SpawnRoom::SpawnRoom(int x, int y) : Room(x, y) {}
std::string SpawnRoom::type() {
    return "Spawn Room";
}

// BuffRoom 
BuffRoom::BuffRoom(int x, int y) : Room(x, y) {}
void BuffRoom::init(){
    //make a random buff and add that to the player statuses
}
std::string BuffRoom::type()
{
    return "Buff Room";
}

// DebuffRoom 
DebuffRoom::DebuffRoom(int x, int y) : Room(x, y) {}
void DebuffRoom::init(){
    //make a random debuff and add that to the player statuses
}
std::string DebuffRoom::type()
{
    return "Debuff Room";
}

// EnemyRoom 
EnemyRoom::EnemyRoom(int x, int y) : Room(x, y) {}
void EnemyRoom::init(){
    //spawn random enemy that is fit for the level
    //init combat
}
std::string EnemyRoom::type()
{
    return "Enemy Room";
}

// ItemRoom 
ItemRoom::ItemRoom(int x, int y) : Room(x, y) {}
void ItemRoom::init(){
    //make random item and add to player 
}
std::string ItemRoom::type(){
    return "Item Room";
}

// BossRoom 
BossRoom::BossRoom(int x, int y) : Room(x, y) {}
void BossRoom::init(){
    //Spawn boss and init fight
}
std::string BossRoom::type()
{
    return "Boss Room";
}
