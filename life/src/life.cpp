// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>
using namespace std;

Grid<string> createGrid(string filename);
void printGrid(const Grid<string>& grid);
void tick(Grid<string>& grid);
int countNeighbours(Grid<string> &grid, int y, int x);

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
            while (true) {
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

int countNeighbours(Grid<string>& grid, int y, int x) {
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


Grid<string> createGrid(string filename) {

    std::ifstream input;
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
