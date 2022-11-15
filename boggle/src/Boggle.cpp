/*
 * This file implements the boggle game.
 *
 */

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "set.h"
#include "lexicon.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::~Boggle() {
    for (int y=0; y<board.nRows; y++) {
        for (int x=0; x<board.nCols; x++) {
            delete board.get(y,x);
        }
    }
}

void Boggle::initiateBoard() {
    board.resize(4, 4);
    int cubeI = 0;
    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            char faceUp = CUBES[cubeI][randomInteger(0,CUBE_SIDES-1)];
            cubeI++;
            Cube *cube = new Cube;
            cube->letter = faceUp;
            cube->visited = false;
            board.set(y,x, cube);
        }
    }
    shuffle(board);
}

void Boggle::initiateBoardPlayer(string conf) {
    initiateBoard();
    int letterI = 0;
    for (int y=0; y<board.nRows; y++) {
        for (int x=0; x<board.nCols; x++) {
            board.get(y,x)->letter = conf[letterI++];
        }
    }
}

void Boggle::printBoard() const {
    for (int y=0; y < board.nRows; y++) {
        for (int x=0; x < board.nCols; x++) {
            //char letter = board.get(y,x)->letter;
            cout << board.get(y, x)->letter << " ";
        }
        cout << endl;
    }
    cout << endl;
}

Set<string> Boggle::getPlayerWords() const {
    return playerWords;
}

Set<string> Boggle::getComputerWords() const {
    return computerWords;
}

int Boggle::getPlayerScore() const {
    return playerScore;
}

int Boggle::getComputerScore() const {
    return computerScore;
}

void Boggle::addPlayerScore(int num) {
    playerScore += num;
}

void Boggle::addComputerScore(int num) {
    computerScore += num;
}

void Boggle::addPlayerWord(string word) {
    playerWords.add(word);
}

Lexicon Boggle::getLexicon() const {
    return english;
}



bool Boggle::wordCanBeFormed(string word) {
    for (int y=0; y < board.nRows; y++) {
        for (int x=0; x < board.nCols; x++) {
           if (board.get(y, x)->letter == word[0]) {
               //board[y][x]->visited = true;
               Grid<Cube> localBoard;
                   localBoard.resize(board.nRows, board.nCols);
                   for (int y=0; y<board.nRows; y++) {
                       for (int x=0; x<board.nCols; x++) {
                           localBoard[y][x] = *board.get(y,x);
                       }
                   }
               bool canBeFormed = helpCanBeFormed(y, x, word.substr(1), localBoard);
               resetVisited();
               if (canBeFormed) return true;
           }
        }
    }
    return false;
}

bool Boggle::helpCanBeFormed(int yCenter, int xCenter, string word, Grid<Cube> localBoard) {
    cout << word << endl;
    if (word.empty()){
        return true;
    }
    localBoard[yCenter][xCenter].visited = true;
    for (int y=yCenter-1; y <= yCenter+1; y++) {
        for (int x=xCenter-1; x <= xCenter+1; x++) {
            if (localBoard.inBounds(y, x) && !localBoard.get(y, x).visited) {
                cout << localBoard.get(y, x).letter << endl;
                if (localBoard.get(y, x).letter == word[0]) {

                    if (helpCanBeFormed(y, x, word.substr(1), localBoard)) return true;
                }
            }
        }
    }
    return false;
}

void Boggle::resetVisited() {
    for (int y=0; y<board.nRows; y++) {
        for (int x=0; x<board.nCols; x++) {
            board[y][x]->visited = false;;
        }
    }
}

void Boggle::playComputer() {
    for (int y=0; y<board.nRows; y++) {
        for (int x=0; x<board.nCols; x++) {
            //board[y][x]->visited = true;
            string prefix = string(1, board[y][x]->letter);
            Grid<Cube> localBoard;
            localBoard.resize(board.nRows, board.nCols);
            for (int y=0; y<board.nRows; y++) {
                for (int x=0; x<board.nCols; x++) {
                    localBoard[y][x] = *board.get(y,x);
                }
            }
            wordFromCube(y, x, prefix, localBoard);
            resetVisited();
        }
    }
}


void Boggle::wordFromCube(int yCenter, int xCenter, string prefix, Grid<Cube> localBoard) {
    //cout << prefix << endl;
    localBoard[yCenter][xCenter].visited = true;
    for (int y = yCenter-1; y <= yCenter+1; y++) {
        for (int x = xCenter-1; x <= xCenter+1; x++) {
            if (localBoard.inBounds(y, x) && !localBoard.get(y, x).visited) {
                string newPrefix = prefix + string(1, localBoard[y][x].letter);
                if (english.containsPrefix(newPrefix)) {
                    wordFromCube(y, x, newPrefix, localBoard);
                }
                if (!computerWords.contains(newPrefix) && english.contains(newPrefix)
                        && newPrefix.length() >= 4 && !playerWords.contains(newPrefix)) {
                    computerWords.add(newPrefix);
                    addComputerScore(newPrefix.length()-3);
                }

            }

        }
    }
}

void Boggle::resetPlayer() {
    playerScore = 0;
    playerWords.clear();
}

void Boggle::resetComputer() {
    computerScore = 0;
    computerWords.clear();
}

// TODO: implement the members you declared in Boggle.h
