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
    int connectionCount(){
        int out=4;
        for (auto c:connections){
            if (c==nullptr) out--;
        }
        return out;
    }
    bool isConnected() {
        return connected;
    }
    virtual string type() {
        return "Empty Room";
    }
};
class SpawnRoom:public Room{
    string type() override{
        return "Spawn Room";
    }
};
class BuffRoom:public Room{
    string type() override{
        return "Buff Room";
    }
};
class DebuffRoom:public Room{
    string type() override{
        return "Debuff Room";
    }
};
class EnemyRoom:public Room{
    string type() override{
        return "Enemy Room";
    }
};
class ItemRoom:public Room{
    string type() override{
        return "Item Room";
    }
};
class BossRoom:public Room{
    string type() override{
        return "Boss Room";
    }
};
class Maze {
    int w;
    int h;
    vector<vector<Room*>> maze;

public:
    Maze(int width, int height) : w(width), h(height), maze(height, vector<Room*>(width, nullptr)) {
        srand(static_cast<unsigned int>(time(0)));
        generateRooms();
    }
    void generateRooms() {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                switch (rand() % 5) {
                    case 0:
                        maze[i][j] = new Room(); // Empty room //TODO: make it so this work with nullptr instead aka find a way to have it never block off rooms
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
        generateMaze(rand()%w,rand()%h);
        generateSpawnAndBoss();
    }
    void generateSpawnAndBoss(){
        vector<pair<int,int>> oneConnection;
        vector<pair<int,int>> maxConnections;
        int max = 0;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int connectionsCount=maze[i][j]->connectionCount();
                if (connectionsCount > max) {
                    max = connectionsCount;
                    maxConnections.clear();
                    maxConnections.push_back({i,j});
                }
                else if (connectionsCount == max) {
                    maxConnections.push_back({i,j});
                }
                if (connectionsCount==1){
                    oneConnection.push_back({i,j});
                }
            }
        }
        int r1=rand()%oneConnection.size(),r2=rand()%maxConnections.size();
        Room* oldRoom = maze[oneConnection[r1].first][oneConnection[r1].second];
        maze[oneConnection[r1].first][oneConnection[r1].second]= new BossRoom();
        maze[oneConnection[r1].first][oneConnection[r1].second]->connected = oldRoom->connected;
        for (int i = 0; i < 4; ++i) maze[oneConnection[r1].first][oneConnection[r1].second]->connections[i] = oldRoom->connections[i];
        delete oldRoom;
        oldRoom = maze[maxConnections[r2].first][maxConnections[r2].second];
        maze[maxConnections[r2].first][maxConnections[r2].second]= new SpawnRoom();
        maze[maxConnections[r2].first][maxConnections[r2].second]->connected = oldRoom->connected;
        for (int i = 0; i < 4; ++i) maze[maxConnections[r2].first][maxConnections[r2].second]->connections[i] = oldRoom->connections[i];
        delete oldRoom;
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
                if (maze[y][x]->type() == "Spawn Room") {
                    out += (maze[y][x]->connections[S] != nullptr) ? "!" : "L";
                    out+=((maze[y][x]->connections[E] != nullptr)?" ":"|");
                } 
                else if (maze[y][x]->type() == "Boss Room") {
                    out += "+|";
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
    Maze maze(5,5);
    cout<<""<<maze.toString();
    return 0;
}
