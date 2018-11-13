#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include "Direction.hpp"
#include <random>
#include <vector>
#include <tuple>
#include <utility>

using namespace std;

class MazeGen: public MazeGenerator
{ 
   public:

    MazeGen();

   virtual void generateMaze (Maze & maze);
    
   void recur_call(Maze & maze);

   bool check_vector(int cellx, int celly);
   
   void get_prev_cell( Maze & maze, std :: vector <std :: pair<int,int>> temp);

   std :: vector <Direction> GetDirection(Maze & maze);

   private:

   int cellX = 0;
   int cellY = 0;
   std :: vector <std :: pair<int,int>> v;
   std :: vector <std :: pair<int,int>> v2;
   std::random_device device;
   std ::default_random_engine engine{device()};
   std:: uniform_int_distribution<int> distribution{1,4};
};
