// Evil hangman
// Plays hangman with the user. Being evil by not having a
// chosen word and constantly picking a the hardest group of words
// matching the guesses.

#include <iostream>
#include <string>
#include <unordered_set>
#include <list>
#include <fstream>
#include <iterator>
#include <set>
#include <map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void createDict(unordered_set<int>& wordLengths, list<string>& dict);
bool wordLengthExists(int length, const unordered_set<int>& lengths);
void keepLength(list<string>& dictionary, const unsigned int length);
string largestWordFamily(char guess, list<string>& dict, string currentWord);
bool isComplete(string currentWord);


int main() {
    bool play = true;
    while (play) {
        cout << endl <<"Welcome to Hangman." << endl;

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

        keepLength(dictionary, wordLength);

        set<char> usedLetters;
        string currentWord = string(wordLength, '-');
        char guess;
        bool won = isComplete(currentWord);

        while(guesses && !won) {

            cout << "Number of guesses left: " << guesses << endl;
            if(showRemaining) {
                cout << "Number of words left: " << dictionary.size() << endl;
            }

            cout << endl << currentWord << endl;

            do {
                cout << endl << "Make a guess: ";
                cin >> guess;

            } while (usedLetters.find(guess) != usedLetters.end());
            currentWord = largestWordFamily(guess, dictionary, currentWord);

            won = isComplete(currentWord);
            guesses--;
        }

        if(won) {
            cout << "Congratulations my man! The word was " << currentWord << "!!" << endl;

        }
        do {
            cout << "Wanna play again? (y/n) ";
            cin >> input;
        } while (input != "y" && input != "n");
        play = input == "y";
    }

    cout << "See you later alligator " << endl;

    return 0;
}

bool isComplete(string currentWord) {
    return (currentWord.find('-') == std::string::npos);
}


string largestWordFamily(char guess, list<string>& dict, string currentWord) {
    map<string, list<string>> families;
    for(list<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
        string mapKey;
        for(list<string>::size_type i = 0; i < (*it).length(); i++) {
             if((*it)[i] == guess && mapKey[i] != '-') {
                 mapKey += guess;
             } else {
                 mapKey += currentWord[i];
             }
        }
        if(families.find(mapKey) == families.end()) {
            families.insert({mapKey, list<string> {*it}});
        } else {
            families[mapKey].push_front(*it);
        }
    }
    string largestKey = currentWord;
    if(families.size()) {

        map<string, list<string>>::iterator it = families.begin();
        largestKey = it->first;
        list<string> largest = it++->second;
        while(++it != families.end()) {
            if(it->second.size() > largest.size()) {
                largest = it->second;
                largestKey = it->first;
            }
        }
        dict = largest;
    }
    return largestKey;
}


bool wordLengthExists(int length, const unordered_set<int>& lengths) {
    return lengths.count(length) >= 1;
}

void keepLength(list<string>& dictionary, const unsigned int length) {
    list<string> res;
    for(list<string>::iterator it = dictionary.begin(); it != dictionary.end(); ++it) {
        if ((*it).length() == length) {
            res.push_front(*it);
        }
    }
    dictionary = res;
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
