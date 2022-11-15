// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

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
    for (int y=0; y<board.nRows - 1; y++) {
        for (int x=0; x<board.nCols - 1; x++) {
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

int Boggle::getPlayerScore() const {
    return playerScore;
}

void Boggle::addPlayerScore(int num) {
    playerScore += num;
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
               word.erase(0);
               board[y][x]->visited = true;
               bool canBeFormed = helpCanBeFormed(y, x, word);
               resetVisited();
               if (canBeFormed) return true;
           }
        }
    }
    return false;
}

bool Boggle::helpCanBeFormed(int yCenter, int xCenter, string word) {
    cout << word << endl;
    if (word.empty()){
        return true;
    }
    for (int y=yCenter-1; y <= yCenter+1; y++) {
        for (int x=xCenter-1; x <= xCenter+1; x++) {
            if (board.inBounds(y, x) && !board.get(y, x)->visited) {
                cout << board.get(y, x)->letter << endl;
                if (board.get(y, x)->letter == word[0]) {
                    word.erase(0);
                    board[y][x]->visited = true;
                    if (helpCanBeFormed(y, x, word)) return true;
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

// TODO: implement the members you declared in Boggle.h
