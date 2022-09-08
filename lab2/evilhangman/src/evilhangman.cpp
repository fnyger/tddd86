#include <iostream>
#include <string>
#include <unordered_set>
#include <list>
#include <fstream>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void createDict(unordered_set<int>& wordLengths, list<string>& dict);
bool wordLengthExists(int length, const unordered_set<int>& lengths);


int main() {
    cout << "Welcome to Hangman." << endl;

    list<string> dictionary;
    unordered_set<int> wordLengths;

    createDict(wordLengths, dictionary);



    int wordLength;
    bool validWord = false;
    while(!validWord) {
        cout << "Enter word length: ";
        cin >> wordLength;
        validWord = wordLengthExists(wordLength, wordLengths);
    }

    int guesses = 0;
    while (guesses <= 0) {
        cout << endl << "Enter number of guesses: ";
        cin >> guesses;
    }

    bool showRemaining = false;
    string input;
    do {
        cout << "Show number of words left? (y/n) ";
        cin >> input;
    } while (input != "y" && input != "n");
    showRemaining = input == "y";





    return 0;
}

bool wordLengthExists(int length, const unordered_set<int>& lengths) {
    return lengths.count(length) >= 1;
}


void createDict(unordered_set<int>& wordLengths, list<string>& dict) {
    ifstream input;
    input.open("dictionary.txt");
    string line;
    while (getline(input, line)) {
        dict.push_front(line);
        wordLengths.insert(line.length());
    }
}
