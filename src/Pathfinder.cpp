#include <vector>
#include <deque>
#include <iostream>
using namespace std;

template<size_t rows, size_t cols>
vector<char> pathfinder(char (&maze)[rows][cols]);

struct node{
  int x;
  int y;
  //the vector that has the path to the finish
  vector<char> path;
  //constructor for the struct node
  node(int x, int y, vector<char> path, char a){
    this->x = x;
    this->y = y;
    this->path = path;
    this->path.push_back(a);
  }
  //default constructor
  node(int x, int y){
    this->x = x;
    this->y = y;
  }
};

//this checks to see if we have fallen outside the bound of the 2D array.
template<size_t rows, size_t cols>
bool withinBounds(int i, int j){
  if((i >= 0) && ((unsigned int)i < rows) && (j >= 0) && ((unsigned int)j < cols))
    return true;
  else
    return false;
}

template<size_t rows, size_t cols>
vector<char> pathfinder(char (&maze)[rows][cols]){
  deque<node> coord;
  unsigned int x = 0, y = 0;
  unsigned int i,j;

  //we search through the maze to find the start and set its x and y
  //coordinates
  for(i = 0; i < rows; i++){
    for(j = 0; j < cols; j++){
      if(maze[i][j] == 's'){
        x = i;
        y = j;
      }
    }
  }

  //push the start coordinates to the queue
  coord.push_back(node(x, y));

  //creates a visited 2D array that is the same size as your maze
  //and it initilizes everything in that array to 0
  int visited[rows][cols];
  for(i = 0; (unsigned int)i < rows; i++){
    for(j = 0; (unsigned int)j < cols; j++){
      visited[i][j] = 0;
    }
  }

  //continue to loop through as long as the queue is not empty
  while(!coord.empty()){
    //store and then pop off the top of the queue
    node current = coord.front();
    coord.pop_front();

    //mark that node as visited
    visited[current.x][current.y] = 1;

    //base case if the thing we pop off is the finish
    if(maze[current.x][current.y] == 'f'){
      return current.path;
    }

    //the next 4 if statements check the cardinal coordinates of the node we popped off
    //the if statements only pass if it is within the bounds, it is not a wall, and it hasn't been
    //visited
    if(withinBounds<rows,cols>(current.x + 1, current.y)
      && (visited[current.x + 1][current.y] != 1) && maze[current.x + 1][current.y] != 'w'){
        coord.push_back(node(current.x + 1, current.y, current.path, 'D'));
    }
    if(withinBounds<rows,cols>(current.x, current.y - 1)
      && (visited[current.x][current.y - 1] != 1) && maze[current.x][current.y - 1] != 'w'){
        coord.push_back(node(current.x, current.y - 1, current.path, 'L'));
    }
    if(withinBounds<rows,cols>(current.x, current.y + 1)
      && (visited[current.x][current.y + 1] != 1) && maze[current.x][current.y + 1] != 'w'){
        coord.push_back(node(current.x, current.y + 1, current.path, 'R'));
    }
    if(withinBounds<rows,cols>(current.x - 1, current.y)
      && (visited[current.x - 1][current.y] != 1) && maze[current.x - 1][current.y] != 'w'){
        coord.push_back(node(current.x - 1, current.y, current.path, 'U'));
    }
  }

  //this is only reached if their is not a path the finish and it proceeds to return the
  //Null character
  vector<char> result;
  result.push_back('\0');
  return result;
}

int main(void){
  char arr[15][20] =
  {
  	{'s','w','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'},
  	{'e','w','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'},
  	{'e','w','e','w','w','w','w','w','w','w','w','w','w','w','w','w','e','w','w','w'},
  	{'e','w','e','w','w','e','e','e','e','e','e','e','e','e','e','e','e','w','w','w'},
  	{'e','w','e','w','w','w','w','w','w','w','w','w','w','w','w','w','e','w','w','w'},
  	{'e','w','e','w','e','e','e','e','e','e','e','e','e','e','e','e','e','w','w','w'},
  	{'e','w','e','w','e','w','w','w','w','w','w','w','e','e','e','e','e','w','w','w'},
  	{'e','w','e','w','e','e','e','e','e','e','e','w','e','w','w','w','w','w','w','e'},
  	{'e','w','e','w','e','e','w','e','w','e','w','w','e','w','e','e','e','e','w','e'},
  	{'e','w','e','w','e','w','w','f','w','e','w','e','e','w','e','w','w','e','w','e'},
  	{'e','w','e','w','e','e','w','e','w','w','w','e','e','w','e','e','w','e','w','e'},
  	{'e','w','e','w','e','e','e','e','e','e','w','w','e','w','e','e','w','e','e','e'},
  	{'e','w','e','w','e','e','e','e','e','e','e','w','e','w','e','e','w','e','e','e'},
  	{'e','e','e','w','e','e','e','e','e','e','e','w','e','w','w','w','w','e','e','e'},
  	{'e','w','e','w','e','e','e','e','e','e','w','e','e','e','e','e','e','e','e','e'},
  };

  vector<char> steps = pathfinder(arr);
  for(auto i : steps){
    cout << i << " ";
  }
  cout << endl;
  cout << steps.size();
  cout << endl;
  return 0;
}
