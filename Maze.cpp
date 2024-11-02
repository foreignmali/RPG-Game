#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
using namespace std;
enum Direction{N,E,S,W};
class Room{
public:
    bool connected = false;
    // Array of room connections in each direction (N, E, S, W)
    Room* connections[4] = { nullptr, nullptr, nullptr, nullptr };
    // Connect to another room in the specified direction
    void connect(Direction direction, Room* room) {
        connections[direction] = room;
        room->connections[(direction + 2) % 4] = this;  // Connect back in the opposite direction
        connected = true;
        room->connected = true;
    }
    bool isConnected() {
        return connected;
    }
};
class SpawnRoom:public Room{
    
};
class BuffRoom:public Room{
    
};
class DebuffRoom:public Room{
    
};
class EnemyRoom:public Room{
    
};
class ItemRoom:public Room{
    
};
class BossRoom:public Room{
    
};
class Maze {
    const int w = 5;
    const int h = 5;

    vector<vector<Room*>> maze;

public:
    Maze() : maze(h, vector<Room*>(w, nullptr)) {
        srand(static_cast<unsigned int>(time(0)));
    }

    void generateRooms() {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                switch (rand() % 5) {
                    case 0:
                        maze[i][j] = new Room(); // Empty room //TODO: make it so this work with nullptr instead
                        break;
                    case 1:
                        maze[i][j] = new BuffRoom(); // Create Buff room
                        break;
                    case 2:
                        maze[i][j] = new DebuffRoom(); // Create Debuff room
                        break;
                    case 3:
                        maze[i][j] = new EnemyRoom(); // Create Enemy room
                        break;
                    case 4:
                        maze[i][j] = new ItemRoom(); // Create Item room
                        break;
                    default:
                        maze[i][j] = nullptr; // Fallback
                        break;
                }
            }
        }
    }
    vector<pair<int, int>> directions = {
            {1, 0},   // Move E
            {0, 1},   // Move S
            {-1, 0},  // Move W
            {0, -1}   // Move N
    };
    Direction mapDirection(int dx, int dy) {
        if (dx == 1 && dy == 0) return E;
        if (dx == -1 && dy == 0) return W;
        if (dx == 0 && dy == 1) return S;
        if (dx == 0 && dy == -1) return N;
        throw invalid_argument("Invalid direction");
    }
    random_device rd; 
    mt19937 eng{rd()}; 
    bool isInBounds(int x, int y) {
        return x >= 0 && x < w && y >= 0 && y < h;
    }
    //following backtracking algorithm described here: https://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking
    void generateMaze(int x,int y){
        if (maze[y][x] == nullptr) return;
        //cout<<x<<" "<<y<<endl<<toString(); // print it step by step
        shuffle(directions.begin(), directions.end(), eng);
        for (auto& dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if (isInBounds(nx, ny) && maze[ny][nx] != nullptr && !maze[ny][nx]->isConnected()) {
                maze[y][x]->connect(mapDirection(dir.first, dir.second), maze[ny][nx]);
                generateMaze(nx, ny);
            }
        }
    }
    string toString(){
        string out=" "+string((w * 2) - 1, '_')+"\n";
        for (int y = 0; y < h; ++y) {
            out+="|";
            for (int x = 0; x < w; ++x) {
                //cout<<"I here "<<y<<" "<<x<<endl;
                if (maze[y][x] == nullptr) {
                    out += "||";
                } 
                else {
                    out += (maze[y][x]->connections[S] != nullptr) ? " " : "_";
                    if (maze[y][x]->connections[E] != nullptr) {
                        out+=(maze[y][x]->connections[S] != nullptr || (x+1<w&&maze[y][x+1]->connections[S] != nullptr))?" " : "_";
                    } 
                    else {
                        out+= "|";
                    }
                }
            }
            out+="\n";
        }
        return out;
    }
    ~Maze() {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                delete maze[i][j]; // Delete the room objects
            }
        }
    }
    
};
//dummy main for testing
int main() {
    Maze maze;
    maze.generateRooms();
    maze.generateMaze(0, 0);
    cout<<""<<maze.toString();
    return 0;
}
