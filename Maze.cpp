#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
class Room{
    
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
    const int w = 21;
    const int h = 21;

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
                        maze[i][j] = nullptr; // Empty room
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
    void generateBoss(){
        maze[rand()%h][rand()%w]=new BossRoom(); //Create the 1 Boss room
    }
    ~Maze() {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                delete maze[i][j]; // Delete the room objects
            }
        }
    }
    
};
int main(){
        srand((unsigned)time(0));

}