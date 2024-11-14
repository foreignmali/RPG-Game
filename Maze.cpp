#include "maze.h"
#include <algorithm>
#include <climits>

using namespace std;

// Room 
Room::Room(int x, int y) : coordinates({x,y}) {}

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
string SpawnRoom::type() {
    return "Spawn Room";
}

string BuffRoom::type() {
    return "Buff Room";
}

string DebuffRoom::type() {
    return "Debuff Room";
}

string EnemyRoom::type() {
    return "Enemy Room";
}

string ItemRoom::type() {
    return "Item Room";
}

string BossRoom::type() {
    return "Boss Room";
}

// Maze 
Maze::Maze(int width, int height) : w(width), h(height), maze(height, vector<Room*>(width, nullptr)), eng(rd()) {
    srand(static_cast<unsigned int>(time(0)));
    vector<vector<int>> group(height, vector<int>(width, 0));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            group[i][j]=rand() % 5;
        }
    }
    generateRooms(group);
}
Maze::Maze(vector<vector<int>> group) : w(group.size()), h(group[0].size()), maze(group.size(), vector<Room*>(group[0].size(), nullptr)), eng(rd()) {
    srand(static_cast<unsigned int>(time(0)));
    generateRooms(group);
}

void Maze::generateRooms(vector<vector<int>> group) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            switch (group[i][j]) {
                case 0:
                    maze[i][j] = nullptr; // Empty room 
                    break;
                case 1:
                    maze[i][j] = new BuffRoom(j,i); // Create Buff room
                    break;
                case 2:
                    maze[i][j] = new DebuffRoom(j,i); // Create Debuff room
                    break;
                case 3:
                    maze[i][j] = new EnemyRoom(j,i); // Create Enemy room
                    break;
                case 4:
                    maze[i][j] = new ItemRoom(j,i); // Create Item room
                    break;
                default:
                    maze[i][j] = nullptr; // Fallback
                    break;
            }
        }
    }
    vector<vector<Room*>> islands;
    for (int i = 0, n = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (maze[i][j] != nullptr && !maze[i][j]->isConnected()) {
                // Start generating the maze from any unvisited room
                // This will split the maze into islands if rooms are isolated by nullptr
                vector<Room*> temp;
                islands.push_back(temp);
                generateMaze(islands[n++], j, i);
            }
        }
    }
    cout<<"This is n: "<<islands.size()<<endl<<toString(nullptr);
    generatePortals(islands);
    generateSpawnAndBoss();
}
vector<Room*> Maze::getMinConnections(vector<Room*> group){
    vector<Room*> minConnections;
    int min=INT_MAX;
    for (int i = 0; i < group.size(); i++) {
        if (group[i] == nullptr) continue;
        int connectionsCount = group[i]->connectionCount();
        if (connectionsCount < min) {
            min = connectionsCount;
            minConnections.clear();
            minConnections.push_back(group[i]);
        } 
        else if (connectionsCount == min) {
            minConnections.push_back(group[i]);
        }
    }
    return minConnections;
}
vector<Room*> Maze::getMinConnections(vector<vector<Room*>> group){
    vector<Room*> minConnections;
    int min=INT_MAX;
    for (int i = 0; i < group.size(); i++) {
        for (int j = 0; j < group[i].size(); j++) {
            if (group[i][j] == nullptr) continue;
            int connectionsCount = group[i][j]->connectionCount();
            if (connectionsCount < min) {
                min = connectionsCount;
                minConnections.clear();
                minConnections.push_back(group[i][j]);
            } 
            else if (connectionsCount == min) {
                minConnections.push_back(group[i][j]);
            }
        }
    }
    return minConnections;
}
vector<Room*> Maze::getMaxConnections(vector<Room*> group){
    vector<Room*> maxConnections;
    int max=0;
    for (int i = 0; i < group.size(); i++) {
        if (group[i] == nullptr) continue;
        int connectionsCount = group[i]->connectionCount();
        if (connectionsCount > max) {
            max = connectionsCount;
            maxConnections.clear();
            maxConnections.push_back(group[i]);
        } 
        else if (connectionsCount == max) {
            maxConnections.push_back(group[i]);
        }
    }
    return maxConnections;
}
vector<Room*> Maze::getMaxConnections(vector<vector<Room*>> group){
    vector<Room*> maxConnections;
    int max=0;
    for (int i = 0; i < group.size(); i++) {
        for (int j = 0; j < group[i].size(); j++) {
            if (group[i][j] == nullptr) continue;
            int connectionsCount = group[i][j]->connectionCount();
            if (connectionsCount > max) {
                max = connectionsCount;
                maxConnections.clear();
                maxConnections.push_back(group[i][j]);
            } 
            else if (connectionsCount == max) {
                maxConnections.push_back(group[i][j]);
            }
        }
    }
    return maxConnections;
}
void Maze::generatePortals(vector<vector<Room*>> islands){
    if (islands.size()<2) return;

    for (int i = 0; i < islands.size(); i++) islands[i]=getMinConnections(islands[i]);
    std::sort(islands.begin(), islands.end(),[](const std::vector<Room*>& a, const std::vector<Room*>& b) {return a.size()<b.size();});
    vector<vector<bool>> connected(islands.size(),vector<bool>(islands.size(),false));
    vector<vector<bool>> used(islands.size());
    for (int i = 0; i < connected.size(); i++) {
        connected[i][i]=true;
        used[i] = vector<bool>(islands[i].size(), false);
    }
    auto allConnected = [&]() -> bool {
        for (vector<bool> i:connected){
            for (int c:i){
                if (!c) return false;
            }
        }
        return true;
    };
    auto islandFilled = [&](int i) -> bool {
        for (int j = 0; j < used[i].size(); j++){
            if (!used[i][j]) return false;
        }
        return true;
    };
    auto islandFullyConnected = [&](int i) -> bool {
        for (int j = 0; j < connected[i].size(); j++){
            if (!connected[i][j]) return false;
        }
        return true;
    };
    auto OutOfRoomsError = [&](int k) -> bool {
        for (int i=0;i<used.size();i++){
            if(i==k) continue;
            if(!islandFilled(i)) return false;
        }
        if (islandFullyConnected(k)) return false;
        return true;
    };
    while (!allConnected()) {
        bool working = true;
        for(int i=0;!allConnected();i++){
            // solved known edge case by implementing resets (OutOfRoomsError): when two single Room islands are connected before connecting to the rest of the islands aka islands run out of space before being fully connected.
            if (islands[i].empty()) continue;
            pair<Room*,pair<int,int>> ran,dom; // ran is room in island i; dom is room in island not i
            if (OutOfRoomsError(i)) {
                working=false; break;
            }
// cout<<"i";
            int temp;
            do{temp=rand()%islands[i].size();} while (used[i][temp]);
            ran={islands[i][temp],{i,temp}};
            int iterations=0;
            do{dom=pickRandomRoom(islands);}while(connected[i][dom.second.first]||used[dom.second.first][dom.second.second]); // dom cannot have overlapping pair.first which is island number
// cout<<"am";
            // Connect rooms by portal
            maze[ran.first->coordinates.second][ran.first->coordinates.first]->makePortal(maze[dom.first->coordinates.second][dom.first->coordinates.first]);
// cout<<"here";
            // Mark Rooms as used so it won't be picked again
            used[i][temp] = true;
            used[dom.second.first][dom.second.second] = true;
// cout<<"working";
            // Label that these islands are connected
            for (int k = 0; k < connected.size(); k++) {
                if (connected[i][k]) {
                    connected[dom.second.first][k] = true;
                    connected[k][dom.second.first] = true;
                }
            }
            cout<<toString(nullptr)<<endl;
        }
        if (!working) {
            for (int i = 0; i < used.size(); i++){
                for (int j = 0; j < used[i].size(); j++){
                    if(used[i][j]) maze[islands[i][j]->coordinates.second][islands[i][j]->coordinates.first]->clearPortal();
                }
            }
            for (int i = 0; i < islands.size(); i++) {
                fill(connected[i].begin(), connected[i].end(), false);
                connected[i][i] = true;
                fill(used[i].begin(), used[i].end(), false);
            }
        }
    }
}
pair<Room*, pair<int, int>> Maze::pickRandomRoom(vector<vector<Room*>> matrix){
    int totalSize = 0;
    for (const auto& sub : matrix) {
        totalSize += sub.size();
    }
    if (totalSize == 0) {
        throw invalid_argument("All sub-vectors are empty!");
    }
    int r = rand() % totalSize;
    //cout<<"am"<<endl;
    for (int i = 0; i < matrix.size(); i++) {
        if (r < matrix[i].size()) {
            return {matrix[i][r], {i, r}};
        }
        r -= matrix[i].size();
    }
    throw runtime_error("Something went wrong during selection!");
}
void Maze::generateSpawnAndBoss() {
    vector<Room*> minConnections=getMinConnections(maze);
    vector<Room*> maxConnections=getMaxConnections(maze);
    int r1 = rand() % minConnections.size(), r2 = rand() % maxConnections.size();
    //cout<<"I am making bossandspawn"<<minConnections[r1]->coordinates.second<<minConnections[r1]->coordinates.first<<endl; // debug
    Room* oldRoom = maze[minConnections[r1]->coordinates.second][minConnections[r1]->coordinates.first];
    maze[minConnections[r1]->coordinates.second][minConnections[r1]->coordinates.first] = new BossRoom(minConnections[r1]->coordinates.first,minConnections[r1]->coordinates.second);
    maze[minConnections[r1]->coordinates.second][minConnections[r1]->coordinates.first]->connected = oldRoom->connected;
    for (int i = 0; i < 4; ++i) maze[minConnections[r1]->coordinates.second][minConnections[r1]->coordinates.first]->connections[i] = oldRoom->connections[i];
    delete oldRoom;

    oldRoom = maze[maxConnections[r2]->coordinates.second][maxConnections[r2]->coordinates.first];
    maze[maxConnections[r2]->coordinates.second][maxConnections[r2]->coordinates.first] = new SpawnRoom(minConnections[r1]->coordinates.first,minConnections[r1]->coordinates.second);
    maze[maxConnections[r2]->coordinates.second][maxConnections[r2]->coordinates.first]->connected = oldRoom->connected;
    for (int i = 0; i < 4; ++i) maze[maxConnections[r2]->coordinates.second][maxConnections[r2]->coordinates.first]->connections[i] = oldRoom->connections[i];
    delete oldRoom;
}

Direction Maze::mapDirection(int dx, int dy) {
    if (dx == 1 && dy == 0) return E;
    if (dx == -1 && dy == 0) return W;
    if (dx == 0 && dy == 1) return S;
    if (dx == 0 && dy == -1) return N;
    throw invalid_argument("Invalid direction");
}

bool Maze::isInBounds(int x, int y) {
    return x >= 0 && x < w && y >= 0 && y < h;
}
//following backtracking algorithm described here: https://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking
void Maze::generateMaze(vector<Room*> &island, int x, int y) {
    //cout << x << " " << y << endl << toString(); // Print it step by step
    island.push_back(maze[y][x]);
    vector<pair<int, int>> directions = {
        {0, -1}, // Move N
        {1, 0},  // Move E
        {0, 1},  // Move S
        {-1, 0}  // Move W
    };
    
    maze[y][x]->connected = true;
    shuffle(directions.begin(), directions.end(), eng);
    
    for (auto& dir : directions) {
        int nx = x + dir.first;
        int ny = y + dir.second;
        if (isInBounds(nx, ny) && maze[ny][nx] != nullptr && !maze[ny][nx]->isConnected()) {
            maze[y][x]->connect(mapDirection(dir.first, dir.second), maze[ny][nx]);
            generateMaze(island, nx, ny);
        }
    }
}

string Maze::toString(Room* playerRoom) {
    string out = " " + string((w * 2) - 1, '_') + "\n";
    for (int y = 0; y < h; y++) {
        out += "|";
        for (int x = 0; x < w; x++) {
            if (maze[y][x] == nullptr) {
                out += "||";
            } 
            else if (maze[y][x] == playerRoom) {
                if (maze[y][x]->connections[S] == nullptr) {
                    out += "/";  // Wall below player
                } else {
                    out += "X";  // No wall below player
                }
                out += ((maze[y][x]->connections[E] != nullptr) ? " " : "|");
            }
            else if (maze[y][x]->connections[P] != nullptr) {
                out += (maze[y][x]->connections[S] != nullptr) ? "P" : "B";
                    out+=((maze[y][x]->connections[E] != nullptr)?" ":"|");
                } 
            else if (maze[y][x]->type() == "Spawn Room") {
                out += (maze[y][x]->connections[S] != nullptr) ? "!" : "L";
                    out+=((maze[y][x]->connections[E] != nullptr)?" ":"|");
            } 
            else if (maze[y][x]->type() == "Boss Room") {
                out += (maze[y][x]->connections[S] != nullptr) ? "-" : "=";
                out+=((maze[y][x]->connections[E] != nullptr)?" ":"|");
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

Room* Maze::getSpawnRoom(){
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (maze[i][j] && maze[i][j]->type() == "Spawn Room") {
                return maze[i][j];
            }
        }
    }
    return nullptr;
}

Room* Maze::getBossRoom(){
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (maze[i][j] && maze[i][j]->type() == "Boss Room") {
                return maze[i][j];
            }
        }
    }
    return nullptr;
}

Maze::~Maze(){
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            delete maze[i][j]; // Delete the room objects
        }
    }
}
// TO-DO: Maybe make a hidden buff for after you chnage islands that make your rewards better to make portals sound cooler.
