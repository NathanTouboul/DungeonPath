#include <iostream>
#include <array>
#include <string>
#include <queue>


/* Dungeon problem
Finding the shortest path on a grid 
using the Breadth First Search (BFS) algorithm on an unweighted graph.
*/

// Global variable
// Number of rows and columns of the grid
const int nRows = 5;
const int nCols = 7;

template <typename T>
void visualizeGrid(std::array<std::array<T, nCols>, nRows> grid);

int main()
{

    std::array<std::array<std::string, nCols>, nRows> grid = {{ {"S", ".", "#", "#", ".", ".", "." },
                                                                {".", "#", ".", "#", ".", ".", "." },
                                                                {".", ".", ".", ".", ".", ".", "." },
                                                                {".", ".", ".", "#", ".", ".", "." },   
                                                                {".", ".", ".", "#", ".", ".", "G" }}};
   

    // Path matrix
    std::array<std::array<std::string, nCols>, nRows> path = grid;   
    visualizeGrid(grid);

    // Point structure
    struct Point 
    {
        int xCoord, yCoord;

        bool operator!=(const Point& second) const
        {
            return (xCoord != second.xCoord || yCoord != second.yCoord);
        }
    };

    // Starting coordinates
    Point start; start.xCoord = 0; start.yCoord = 0;
    
    // Queue for each dimension
    std::queue<int> xCoordQueue{};
    std::queue<int> yCoordQueue{};

    // Counting the number of steps until goal
    int moveCount{};
    int nodesLeftInLayer = 1;
    int nodesInNextLayer{};
    bool reachEnd = false;

    // Visited matrix to keep track
    std::array<std::array<bool, nCols>, nRows> visited{};

    // Directions that can be taken - Sud -> Est -> Nord -> West
    std::array<int, 4> xDirections = {0, 1, 0, 0};
    std::array<int, 4> yDirections = {-1, 0, 1, -1};

    // Vectors of parent to reconstruc the path: parent indicated for each index (child)
    std::array<int, nCols> xCoordParents{};
    std::array<int, nRows> yCoordParents{};

    // BFS Algorithm
    xCoordQueue.push(start.xCoord);
    yCoordQueue.push(start.yCoord);

    visited[start.yCoord][start.xCoord] = true;

    int xCurr = start.xCoord;
    int yCurr = start.yCoord;

    while(!xCoordQueue.empty())
    {
        // Adding in queues
        xCurr = xCoordQueue.front(); xCoordQueue.pop();
        yCurr = yCoordQueue.front(); yCoordQueue.pop();
        // Ending condition
        if (grid[yCurr][xCurr] == "G")
        {
            reachEnd = true;
            break;
        }

        // Adding to the queue the neighbors
        for (size_t i{}; i < 4; i++)
        {
            int xNext = xCurr + xDirections[i];
            int yNext = yCurr + yDirections[i];

            // Invalid values:
            if (xNext < 0 || xNext > nCols - 1) continue;
            if (yNext < 0 || yNext > nRows - 1) continue;
            if (visited[yNext][xNext]) continue;
            if (grid[yNext][xNext] == "#") continue;

            // Adding to the queues and keeping track of parents
            xCoordQueue.push(xNext);
            yCoordQueue.push(yNext);
            nodesInNextLayer++;
            xCoordParents[xNext] = xCurr;
            yCoordParents[yNext] = yCurr;

            // Adding to the visited 2d array
            visited[yNext][xNext] = true;

        }

        nodesLeftInLayer--;

        if (nodesLeftInLayer == 0)
        {
            nodesLeftInLayer = nodesInNextLayer;
            nodesInNextLayer = 0;
            moveCount++;
        }

    }

    // If the goal is reached
    int result = (reachEnd) ? moveCount : -1;
    std::cout << "Move Count: "; std::cout << result << " \n";

    for (int xCoord: xCoordParents){std::cout << xCoord << " - ";}
    std::cout << "\n";
    for (int yCoord: yCoordParents){std::cout << yCoord <<" - ";}

    Point destination; destination.xCoord = xCurr; destination.yCoord = yCurr;
    Point reverse = destination;

    int i= 0;
    while(reverse.xCoord != start.xCoord || reverse.yCoord != start.yCoord)
    {
        std::cout << reverse.xCoord << " - " << reverse.yCoord << "\n";

        int xParent = xCoordParents[reverse.xCoord];
        int yParent = yCoordParents[reverse.yCoord];


        path[yParent][xParent] = "x";

        reverse.xCoord = xParent;
        reverse.yCoord = yParent;


        if (i == moveCount -1){break;}
        i++;
    }

    // Visited Nodes
    std::cout << "Path grid: \n"; 
    visualizeGrid(path);

    // Making sure queues are empty
    std::cout << "X queue empty: " <<  std::boolalpha << xCoordQueue.empty() <<"\n";
    std::cout << "Y queue empty: " <<  std::boolalpha << yCoordQueue.empty() <<"\n";
}

template <typename T>
void visualizeGrid(std::array<std::array<T, nCols>, nRows> grid)
{
    for (std::array<T, nCols> longitude: grid)
    {
        for (T state: longitude)
        {
            std::cout << state << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

}
