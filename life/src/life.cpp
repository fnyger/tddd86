// Runs game of life
// Takes name of textfile in res folder and reads a colony
// User has options tick to simulate one generation,
// animate simulates 50 generations and quit exits the program.
// filny841 felra653

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>
using namespace std;

Grid<string> createGrid(string& filename);
void printGrid(const Grid<string>& grid);
void tick(Grid<string>& grid);
int countNeighbours(const Grid<string> &grid, int y, int x);

int main() {

    // TODO: Finish the program!
    cout << "Grid input file name? ";
    string filename;
    cin >> filename;

    Grid<string> grid = createGrid(filename);
    bool run = true;
    string userInput;
    do {
        printGrid(grid);
        cout << endl << endl;
        cout << "a)nimate, t)ick, q)uit? ";
        cin >> userInput;

        if(userInput == "q") {
            run = false;
        } else if (userInput == "a") {
            for (int i=0; i<50; i++) {
                tick(grid);
                printGrid(grid);
                cout << endl << endl;
                pause(200);
            }
        } else if (userInput == "t") {
            tick(grid);
        }
    } while(run);

    cout << "Have a nice Life!";

    return 0;
}

//Simulates one generation in game of life.
void tick(Grid<string>& grid) {
    Grid<string> temp = grid;
    int width = grid.numCols();
    int height = grid.numRows();

    for (int y = 0; y<height; y++) {
        for (int x = 0; x<width; x++) {
            int neighbours = countNeighbours(grid, y, x);
            if (neighbours < 2 || neighbours > 3) {
                temp.set(y, x, "-");
            } else if (neighbours == 3) {
                temp.set(y, x, "X");
            }
        }
    }

    grid = temp;
}

//Counts neighbours to a given cell in the grid.
int countNeighbours(const Grid<string>& grid, int y, int x) {
    int width = grid.numCols();
    int height = grid.numRows();
    int count = 0;

    for (int yOffset = -1; yOffset<2; yOffset++) {
        for (int xOffset = -1; xOffset<2; xOffset++) {
            if(xOffset == 0 && yOffset == 0) { //no offset
                continue;
            }
            int neighX = x + xOffset;
            int neighY = y + yOffset;
            if(neighX >= 0 && neighX < width) {
                if(neighY >= 0 && neighY < height) {
                    if (grid[neighY][neighX] == "X") {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}


//Prints the entire grid
void printGrid(const Grid<string>& grid) {
    int width = grid.numCols();
    int height = grid.numRows();

    for (int y = 0; y<height; y++) {
        for (int x = 0; x<width; x++) {
            cout << grid[y][x];
        }
        cout << endl;
    }
}

//Creates the grid from a given file
Grid<string> createGrid(string& filename) {

    ifstream input;
    input.open("../life/res/" + filename);
    string line;

    getline(input, line);
    int height = stoi(line);
    getline(input, line);
    int width = stoi(line);
    Grid<string> grid(height, width);


    for(int y=0; y<height; y++) {
        getline(input, line);
        for (int x=0; x<width; x++) {
            grid[y][x] = line.at(x);
        }
    }
    return grid;
}
