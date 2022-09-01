// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>
using namespace std;

Grid<string> createGrid();
void printGrid(const Grid<string>& grid);

int main() {

    // TODO: Finish the program!

    Grid<string> grid = createGrid();

    printGrid(grid);

    return 0;
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


Grid<string> createGrid() {

    std::ifstream input;
    input.open("../mycolony.txt");
    string line;

    getline(input, line);
    int height = stoi(line);
    getline(input, line);
    int width = stoi(line);
    Grid<string> grid(height, width);

    getline(input, line); //clear line

    for(int y=0; y<height; y++) {
        getline(input, line);
        for (int x=0; x<width; x++) {
            grid[y][x] = line.at(x);
        }
    }
    return grid;
}
