#include "MazeGen.hpp"
#include <ics46/factory/DynamicFactory.hpp>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MazeGen, "Ketan's Maze Generator (Required)")


MazeGen :: MazeGen()
{
}


//Checks whether or not the cells adjacent have been visited
bool MazeGen :: check_vector(int cellx, int celly)
{  
   pair coord = make_pair(cellx,celly);


   if (std :: find(v.begin(), v.end(), coord) != v.end()){
    return true;
    }

    else{
    return false;
    }

}

// This is an extraneous function that can be used to backtrace recursively as opposed to iteratively
void MazeGen :: get_prev_cell(Maze & maze, vector < pair<int,int>> temp )
{
    vector<Direction> dir;
    dir =  GetDirection(maze);
    if( dir.size()  != 0){
   
    pair val = temp.back();
    cellX = val.first;
    cellY = val.second;
    return;
    }

    temp.pop_back();
    get_prev_cell(maze,temp);
}


// This creates a vector of valid directions given that it is within the bounds and has not been visited
vector <Direction> MazeGen :: GetDirection(Maze & maze)
{
    vector <Direction> final_directions;

   if((cellX +1) < maze.getWidth() &&  check_vector(cellX+1, cellY) == false)  {
             final_directions.push_back( Direction :: right);
                 }

   if((cellX - 1)  >=  0 && check_vector(cellX -1, cellY) == false ){
         final_directions.push_back( Direction :: left);

             }

   if((cellY +1) < maze.getHeight() && check_vector(cellX, cellY+1) == false){
          final_directions.push_back( Direction :: down);

              }
   if((cellY -1) >= 0 && check_vector(cellX, cellY-1) == false  ){
        final_directions.push_back( Direction :: up);
            }

    return final_directions;

}


// Main recursive call that removes walls and back tracks when necessary
void MazeGen :: recur_call(Maze & maze)
{ 

   v.push_back(std::make_pair(cellX,cellY));
       
    vector<Direction> final_directions = GetDirection(maze);
    int count = 1;

    while(final_directions.size() == 0 && v.size() != (maze.getWidth() * maze.getHeight()) ) 
    {
       cellX =v[v.size()-count ].first;
       cellY = v[v.size() - count].second;
       count += 1;
       final_directions = GetDirection(maze);
    }
    

     if(v.size() != (maze.getWidth() * maze.getHeight())){
     int randomnum = rand() % final_directions.size();
     maze.removeWall(cellX,cellY, final_directions[randomnum]);
     
       if(final_directions[randomnum] == Direction :: up){
               cellY -= 1;
                    }

       else if(final_directions[randomnum] == Direction :: down){
               cellY += 1;
              }
       else if(final_directions[randomnum] == Direction :: left){
               cellX -= 1;
              }
       else{
             cellX += 1;
         }



     }
     

   if(v.size() == (maze.getWidth() * maze.getHeight()) ) {
       return;
    }

    else{
    recur_call(maze);
    }


}


// Creates the grid of walls to begin and the calls the main recursive function
void MazeGen :: generateMaze (Maze & maze)
{
    
    maze.addAllWalls();
    recur_call(maze);
}
