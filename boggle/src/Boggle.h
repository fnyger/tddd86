// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <grid.h>
#include <iostream>
#include <string>
#include <set.h>
#include <lexicon.h>
// TODO: include any other header files you need

using namespace std;

class Boggle {

    struct Cube {
        char letter;
        bool visited;
    };

public:
    /*
     * Deletes cubes on board from heap
     */
    ~Boggle();

    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    /*
     * Initiates board with shuffled cubes
     */
    void initiateBoard();

    /*
     * Prints board
     */
    void printBoard() const;

    /*
     * Initiates board with letters from player config.
     * Expects string of length 16
     */
    void initiateBoardPlayer(string conf);

    Set<string> getPlayerWords() const;

    int getPlayerScore() const;

    void addPlayerScore(int num);

    void addPlayerWord(string word);

    Lexicon getLexicon() const;

    bool wordCanBeFormed(string word);

    bool helpCanBeFormed(int yCenter, int xCenter, string word);

    void resetVisited();

    // TODO: decide the public member functions and declare them

private:
    Grid<Cube*> board;
    int playerScore = 0;
    Set<string> playerWords;
    Lexicon english = Lexicon("EnglishWords.dat");
    // TODO: decide the private member variables/functions and declare them

};

#endif
