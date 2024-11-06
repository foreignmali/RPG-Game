#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <string>

using namespace std;

// Enum for Directions
enum Direction { N, E, S, W, P};
// Base class for different types of rooms
class Room {
public:
    pair<int,int> coordinates;
    bool connected = false; // Indicates if the room is connected
    Room* connections[5] = { nullptr, nullptr, nullptr, nullptr, nullptr}; // Connections in each direction and a portal(N, E, S, W, P)

    // Connect to another room in the specified direction
    void connect(Direction direction, Room* room);
    void makePortal(Room* room);

    void clearPortal();

    // Count connections
    int connectionCount();
    
    bool isConnected();
    
    Room(int x,int y);

    // Function to get the type of the room
    virtual string type();
    
    // Virtual destructor to allow derived class destructors to be called
    virtual ~Room() = default;
};

// Derived classes for specific room types
class SpawnRoom : public Room {
    using Room::Room;
    string type() override;
};

class BuffRoom : public Room {
    using Room::Room;
    string type() override;
};

class DebuffRoom : public Room {
    using Room::Room;
    string type() override;
};

class EnemyRoom : public Room {
    using Room::Room;
    string type() override;
};

class ItemRoom : public Room {
    using Room::Room;
    string type() override;
};

class BossRoom : public Room {
    using Room::Room;
    string type() override;
};

// Maze class to generate and manage the maze
class Maze {
    int w; // Width of the maze
    int h; // Height of the maze
    vector<vector<Room*>> maze; // 2D vector to hold the maze
    random_device rd; // Random device for seeding
    mt19937 eng; // Mersenne Twister random number generator

public:
    // Constructor
    Maze(int width, int height);
    
    // Function to generate the rooms in the maze
    void generateRooms();
    vector<Room *> getMinConnections(vector<Room *> group);
    vector<Room *> getMinConnections(vector<vector<Room *>> group);

    vector<Room *> getMaxConnections(vector<Room *> group);
    vector<Room *> getMaxConnections(vector<vector<Room *>> group);

    void generatePortals(vector<vector<Room *>> islands);
    pair<Room*, pair<int, int>> pickRandomRoom(vector<vector<Room*>> matrix);

    // Function to generate spawn and boss rooms
    void generateSpawnAndBoss();
    
    // Function to map direction vectors to the Direction enum
    Direction mapDirection(int dx, int dy);
    
    // Check if coordinates are within bounds
    bool isInBounds(int x, int y);
    
    // Function to generate the maze using backtracking
    void generateMaze(vector<Room*> &island, int x, int y);
    
    // Function to convert the maze to a string for display
    string toString();
    
    // Destructor to clean up the allocated room objects
    ~Maze();
};

#endif // MAZE_H
