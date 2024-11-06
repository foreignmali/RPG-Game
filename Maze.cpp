#include "Maze.h"

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
    generateRooms();
}

void Maze::generateRooms() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            switch (rand() % 5) {
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
                // TO-DO: Either make islands accessable by portal or make new connecting rooms at nullptr
                vector<Room*> temp;
                islands.push_back(temp);
                generateMaze(islands[n++], j, i);
            }
        }
    }
    cout<<"This is n: "<<islands.size()<<endl<<toString();
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

    for (int i = 0; i < islands.size(); i++){
        islands[i]=getMinConnections(islands[i]);
    }
    vector<vector<bool>> connected(islands.size(),vector<bool>(islands.size(),false));
    for (int i = 0; i < connected.size(); i++){
        connected[i][i]=true;
    }
    auto allConnected = [&]() -> bool {
        for (vector<bool> i:connected){
            for (int c:i){
                if (!c) return false;
            }
        }
        return true;
    };
    std::sort(islands.begin(), islands.end(),[](const std::vector<Room*>& a, const std::vector<Room*>& b) {return a.size()<b.size();});
    // for (int i = 0; i < islands.size(); i++){
    //     for (int j = 0; j < islands[i].size(); j++){
    //         cout<<islands[i][j]->coordinates.first<<islands[i][j]->coordinates.second<<endl;
    //     }
    //     cout<<endl;
    // }
    for (int i = 0; i < islands.size(); i++){
        // FUCKING HELL this is confusing because there are 2 pairs of coordinates for the same Room*
        if (islands[i].size()<1||allConnected()) continue;
        pair<Room*,pair<int,int>> ran,dom; // ran is room in island i; dom is room in island not i

        // cout<<"i"<<endl;
        int temp=rand()%islands[i].size();
        ran={islands[i][temp],{i,temp}};
        do{dom=pickRandomRoom(islands);}while(dom.second.first==i||connected[i][dom.second.first]); // dom cannot have overlapping pair.first which is island number
        pair<int,int> r=ran.first->coordinates,r1=dom.first->coordinates;

        // Connect rooms by portal
        // cout<<"am"<<r.first<<r.second<<" "<<r1.first<<r1.second<<endl;
        maze[r.second][r.first]->makePortal(maze[r1.second][r1.first]);

        // Remove the Room from islands so it won't be picked again
        // cout<<"here"<<ran.second.first<<ran.second.second<<" "<<dom.second.first<<dom.second.second<<endl;
        if (islands[ran.second.first].size()<2) islands[ran.second.first].clear();
        else islands[ran.second.first].erase(islands[ran.second.first].begin()+ran.second.second);
        if (islands[dom.second.first].size()<2) islands[dom.second.first].clear();
        else islands[dom.second.first].erase(islands[dom.second.first].begin()+dom.second.second);

        // Label that these islands are connected
        // cout<<"working"<<ran.second.first<<dom.second.first<<" "<<dom.second.first<<ran.second.first<<endl;
        for(int k=0;k<connected.size();k++){
            if(connected[ran.second.first][k]) {
                connected[dom.second.first][k]=true;
                connected[k][dom.second.first]=true;
            }            
        }
        cout<<toString()<<islands[r.second].size()<<islands[r1.second].size()<<endl;
    //     for (int i = 0; i < islands.size(); i++){
    //     for (int j = 0; j < islands[i].size(); j++){
    //         cout<<islands[i][j]->coordinates.first<<" "<<islands[i][j]->coordinates.second<<endl;
    //     }
    //     cout<<endl;
    //     }
    // for (const auto& row : connected) {
    // for (bool val : row) {
    //     cout << val << " ";
    // }
    // cout << endl;
    // }        
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

string Maze::toString() {
    string out = " " + string((w * 2) - 1, '_') + "\n";
    for (int y = 0; y < h; y++) {
        out += "|";
        for (int x = 0; x < w; x++) {
            if (maze[y][x] == nullptr) {
                out += "||";
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
Maze::~Maze(){
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            delete maze[i][j]; // Delete the room objects
        }
    }
}
int main(){
    Maze test(5,5);
    cout<<test.toString();
}
