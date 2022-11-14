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

void Boggle::mapGrid() {
    for (int y=0; y < board.nRows; y++) {
        for (int x=0; x < board.nCols; x++) {
            if (!lettersMapped.containsKey(board.get(y,x)->letter)) {
                lettersMapped.put(board.get(y,x)->letter, 1);
            } else {
                lettersMapped[board.get(y,x)->letter] = //
                        lettersMapped.get(board.get(y,x)->letter)+1;
            }
        }
    }
}

Map<char, int> Boggle::mapWord(string word) {
    Map<char, int> wordMapped;
    for (char letter : word) {
        if (!wordMapped.containsKey(letter)) {
            wordMapped.put(letter, 1);
        } else {
            wordMapped[letter] = wordMapped.get(letter) + 1;
        }
    }
    return wordMapped;
}

bool Boggle::wordCanBeFormed(string word) {
    cout << "test" << endl;
    Map<char, int> wordMapped = mapWord(word);
    for (char letter : wordMapped) {
        if (!lettersMapped.containsKey(letter)  || lettersMapped[letter] < wordMapped[letter]) {
            return false;
        }
    }
    return true;
}

Map<char, int> Boggle::getLettersMapped() const {
   return lettersMapped;
}
// TODO: implement the members you declared in Boggle.h
