/*
 * This file handles the I/O with the player through the terminal
 *
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
// TODO: include any other header files you need

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)
    if(!yesOrNo("Do you want to generate a random board? (y/n) ")) {
        cout << "Write 16 character long string: ";
        string boardConf;
        getline(cin, boardConf);
        boardConf = toUpperCase(boardConf);
        boggle.initiateBoardPlayer(boardConf);
    } else {
        boggle.initiateBoard();
    }
    cout << "It's your turn!" << endl;
    boggle.printBoard();

    bool userTurn = true;
    while(userTurn) {

        cout << "Your words (" << boggle.getPlayerWords().size() << "): " << //
                boggle.getPlayerWords() << endl;
        cout << "Your score: " << boggle.getPlayerScore() << endl;
        cout << "Type a word (or press Enter to end your turn): ";
        string word;
        getline(cin, word);
        word = toUpperCase(word);
        clearConsole();
        if (word.empty()) {
            userTurn = false;
        } else if (word.length() < 4) {
            cout << "That word is not long enough." << endl;
        } else if (boggle.getPlayerWords().contains(word)) {
            cout << "You have already guessed that word." << endl;
        } else if (!boggle.getLexicon().contains(word)) {
            cout << "That word is not in the dictionary." << endl;
        } else if (!boggle.wordCanBeFormed(word)) {
            cout << "That word can't be formed on this board." << endl;
        } else {
            cout << "You found a new word! \"" << word << "\"" << endl;
            boggle.addPlayerWord(word);
            boggle.addPlayerScore(word.length()-3);
        }


        boggle.printBoard();


    }
    cout << "It's my turn!" << endl;
    boggle.playComputer();
    cout << "My words (" << boggle.getComputerWords().size() << "): " << //
            boggle.getComputerWords() << endl;
    cout << "My score: " << boggle.getComputerScore() << endl;
    cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
    boggle.resetPlayer();
    boggle.resetComputer();
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
