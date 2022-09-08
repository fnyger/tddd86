#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

unordered_set<string> createDict();
stack<string> wordChain(string w1, string w2);
bool validWord(string word, const unordered_set<string>& dictionary);
bool used(string newWord, const unordered_set<string>& usedWords);




int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    string w1, w2;
    cin >> w1;
    cin >> w2;

    cout << "Chain from data back to code:" << endl;

    stack<string> chain = wordChain(w1, w2);

    do {
        cout << chain.top() << " ";
        chain.pop();
    } while(!chain.empty());


    cout << endl << "Have a nice day!" << endl;

    return 0;
}

stack<string> wordChain(string w1, string w2) {

    stack<string> startStack;
    startStack.push(w1);
    queue<stack<string>> stacks;
    stacks.push(startStack);

    unordered_set<string> dictionary = createDict();
    unordered_set<string> usedWords;


    while(!stacks.empty()) {
        stack<string> workStack = stacks.front();
        stacks.pop();
        if(workStack.top() == w2) {
            return workStack;
        } else {
            string currentWord = workStack.top();
            for(int i = 0; i < currentWord.length(); i++) {
                for(const char& c : ALPHABET) {
                    string newWord = currentWord;
                    newWord[i] = c;
                    if(validWord(newWord, dictionary)) {

                        if(!used(newWord, usedWords)) {
                            usedWords.insert(newWord);
                            stack<string> newStack (workStack);
                            newStack.push(newWord);
                            stacks.push(newStack);
                        }
                    }
                }
            }
        }
    }
}

bool validWord(string word, const unordered_set<string>& dictionary) {
    return dictionary.count(word) >= 1;

}

bool used(string newWord, const unordered_set<string>& usedWords) {
    return usedWords.count(newWord) >= 1;
}

unordered_set<string> createDict() {

    ifstream input;
    input.open("dictionary.txt");
    string line;
    unordered_set<string> dict;
    while (getline(input, line)) {
        dict.insert(line);
    }
    return dict;
}
