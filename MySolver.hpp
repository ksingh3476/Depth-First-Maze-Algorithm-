#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include <vector>
#include <utility>
#include <random>


class MySolver: public MazeSolver
{   
    public:

    MySolver();

    virtual void solveMaze(const Maze & maze, MazeSolution & mazeSolution);

    void recursive_call(const Maze & maze, MazeSolution & mazeSolution);

    std :: vector <Direction> getdirections(const Maze & maze, MazeSolution & mazeSolution);
    
    bool check_visit ( int cellx, int celly);
    
    private:

    std :: vector <std :: pair<int,int>> visitedcells;
    int cellX;
    int cellY;
};
