#include "MySolver.hpp"
#include <ics46/factory/DynamicFactory.hpp>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, MySolver, "Ketan's Maze Solver (Required)")

MySolver :: MySolver()
{
}
// Gathers starting cell and calls the main recursive call
void MySolver :: solveMaze(const Maze & maze, MazeSolution & mazeSolution)
{
    std::  pair temp = mazeSolution.getStartingCell();
    cellX = temp.first;
    cellY = temp.second;
    recursive_call(maze,mazeSolution);
}

//Ensures that the solver does not loop infinitely by checking if the cell has been visited
bool MySolver :: check_visit ( int cellx, int celly) 
{
    std:: pair coord = std :: make_pair(cellx,celly);
    
    if (std :: find(visitedcells.begin(), visitedcells.end(), coord) != visitedcells.end()){
      return true;
    }
    
    else{
      return false;
    }
} 

// Gathers all possible directions that do not have a wall and have not been visited
std :: vector <Direction> MySolver :: getdirections(const Maze & maze, MazeSolution & mazeSolution)
{
    std :: vector <Direction> posdir;      
    
    if(!maze.wallExists( cellX, cellY, Direction :: right) && cellX +1 < maze.getWidth() && check_visit(cellX+1,cellY)  == false ){
      posdir.push_back(Direction :: right);
    } 
    
    if(! maze.wallExists( cellX, cellY, Direction :: left) && cellX-1 >= 0  && check_visit(cellX-1,cellY) == false  ){
      posdir.push_back(Direction :: left);
    }
    
    if(! maze.wallExists( cellX, cellY , Direction :: up) && cellY-1 >= 0 && check_visit(cellX, cellY-1  )  == false   ){
      posdir.push_back(Direction :: up);
    }  
    
    if(! maze.wallExists( cellX , cellY, Direction :: down)  && cellY +1 < maze.getHeight() && check_visit (cellX,cellY+1  )  == false   ){
      posdir.push_back(Direction :: down);
    }
    
    return posdir;   
}
// Main recursive function that extends  the mazesolution in a possible direction and backtracks when necessary
void MySolver :: recursive_call(const Maze & maze, MazeSolution & mazeSolution)
{
  
    visitedcells.push_back(std :: make_pair(cellX,cellY)) ;
    
    std:: vector<Direction> possibledir = getdirections(maze,mazeSolution);
    
    while(possibledir.size() == 0){
      mazeSolution.backUp();
      cellX = mazeSolution.getCurrentCell().first;
      cellY = mazeSolution.getCurrentCell().second;
      possibledir = getdirections(maze,mazeSolution);
      
    }
      
    
    mazeSolution.extend(possibledir[0]);
        
    if(possibledir[0] == Direction :: up){
      cellY -= 1;
    }
    else if(possibledir[0] == Direction :: down){
      cellY += 1;
    }
    else if(possibledir[0] == Direction :: left){
      cellX -= 1;
    }
    else{
      cellX += 1;
    }
      
    
    if(mazeSolution.isComplete()){
      return;
    }
    else{
      recursive_call(maze, mazeSolution);
    }
}

