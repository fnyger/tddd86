// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "HuffmanNode.h"
#include <queue>
using namespace std;
// TODO: include any other headers you need

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    while(input) {
        char newChar = input.get();
        if (newChar == -1) break;
        if (freqTable.count(newChar)) {
            freqTable[newChar] += 1;
        } else {
            freqTable.emplace(newChar, 1);
        }
    }
    freqTable.emplace(PSEUDO_EOF, 1);
    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    priority_queue<HuffmanNode> huffManQueue;
    for (auto it = freqTable.begin(); it != freqTable.end();it++){
            HuffmanNode node = HuffmanNode(it->first,it->second);
            huffManQueue.push(node);
        }
    HuffmanNode parent;
    while(huffManQueue.size() > 1) {
        HuffmanNode* firstChild = new HuffmanNode(huffManQueue.top().character, huffManQueue.top().count,//
                                                  huffManQueue.top().zero, huffManQueue.top().one);
        huffManQueue.pop();
        HuffmanNode* secondChild = new HuffmanNode(huffManQueue.top().character, huffManQueue.top().count,//
                                                  huffManQueue.top().zero, huffManQueue.top().one);
        huffManQueue.pop();
        parent = HuffmanNode(NOT_A_CHAR, firstChild->count+secondChild->count, firstChild, secondChild);
        huffManQueue.push(parent);
    }
    return new HuffmanNode(huffManQueue.top().character, huffManQueue.top().count,//
                            huffManQueue.top().zero, huffManQueue.top().one);
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    map<int, string> encodingMap;
    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
