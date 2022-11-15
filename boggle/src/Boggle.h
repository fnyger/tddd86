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

    /*
     * Get set of player words
     */
    Set<string> getPlayerWords() const;

    Set<string> getComputerWords() const;

    int getComputerScore() const;

    void addComputerScore(int num);

    /*
     * Get player score
     */
    int getPlayerScore() const;

    /*
     * Increase player score
     */
    void addPlayerScore(int num);


    /*
     * Append player word
     */
    void addPlayerWord(string word);

   /*
    * Get english lexicon
    */
    Lexicon getLexicon() const;

    /*
     * Returns if word can be formed on board
     */
    bool wordCanBeFormed(string word);

    void resetVisited();

    void playComputer();

    void resetPlayer();

    void resetComputer();



private:
    void addWordsFromBoard();

    void wordFromCube(int yCenter, int xCenter, string prefix, Grid<Cube> localBoard);
    /*
     * Helper function for can be formed
     */
    bool helpCanBeFormed(int yCenter, int xCenter, string word, Grid<Cube> localBoard);

    /*
     * The board
     */
    Grid<Cube*> board;

    /*
     * Player score
     */
    int playerScore = 0;
    int computerScore = 0;
    Set<string> computerWords;

    /*
     * Set of entered player words
     */
    Set<string> playerWords;

    /*
     * The english lexicon
     */
    Lexicon english = Lexicon("EnglishWords.dat");
    // TODO: decide the private member variables/functions and declare them

};

#endif
