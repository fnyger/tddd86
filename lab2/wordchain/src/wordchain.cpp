#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

map<string, bool> createDict();


int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: " << endl;

    queue<stack<string>> stacks;

    map<string, bool> dict = createDict();

    cout << dict["zebsdfgsdfgra"] << endl;

    // TODO: Finish the program!

    return 0;
}

map<string, bool> createDict() {

    ifstream input;
    input.open("dictionary.txt");
    string line;
    map<string, bool> dict;
    while (getline(input, line)) {
        dict[line] = true;
    }
    return dict;
}
