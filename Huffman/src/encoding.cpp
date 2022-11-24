// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "bitstream.h"
#include <queue>
using namespace std;
// TODO: include any other headers you need

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    char newChar;
    while((newChar = input.get()) != -1) {
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
    for (auto it = freqTable.begin(); it != freqTable.end(); it++){
            HuffmanNode node = HuffmanNode(it->first,it->second);
            huffManQueue.push(node);
        }
    while(huffManQueue.size() > 1) {
        HuffmanNode* firstChild = new HuffmanNode(huffManQueue.top().character, huffManQueue.top().count,//
                                                  huffManQueue.top().zero, huffManQueue.top().one);
        huffManQueue.pop();
        HuffmanNode* secondChild = new HuffmanNode(huffManQueue.top().character, huffManQueue.top().count,//
                                                  huffManQueue.top().zero, huffManQueue.top().one);
        huffManQueue.pop();
        HuffmanNode parent(NOT_A_CHAR, firstChild->count+secondChild->count, firstChild, secondChild);
        huffManQueue.push(parent);
    }
    HuffmanNode* root = new HuffmanNode(huffManQueue.top().character, huffManQueue.top().count,//
                                        huffManQueue.top().zero, huffManQueue.top().one);
    return root;
}

void traverse(HuffmanNode* encodingTree, string code, map<int, string>& encodingMap) {
    if (encodingTree->isLeaf()) {
        encodingMap.emplace(encodingTree->character, code);
        return;
    }
    traverse(encodingTree->zero, code+"0", encodingMap);
    traverse(encodingTree->one, code+"1", encodingMap);
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    traverse(encodingTree, "", encodingMap);
    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    // TODO: implement this function
    int currentByte;

    while((currentByte = input.get()) != -1) {
        for(unsigned i = 0; i < encodingMap.at(currentByte).size(); ++i) {
            if (encodingMap.at(currentByte)[i] == '1') {
                output.writeBit(1);
            } else {
                output.writeBit(0);
            }

        }
    }
    for(unsigned i = 0; i < encodingMap.at(PSEUDO_EOF).size(); ++i) {
        if (encodingMap.at(PSEUDO_EOF)[i] == '1') {
            output.writeBit(1);
        } else {
            output.writeBit(0);
        }
    }

}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    int currentBit;
    HuffmanNode* currNode = encodingTree;
    while((currentBit = input.readBit()) != -1) {
        if (currentBit == 0) {
            currNode = currNode->zero;
        } else {
            currNode = currNode->one;
        }

        if (currNode->isLeaf()) {
            if (currNode->character == PSEUDO_EOF) break;
            output.put(currNode->character);
            currNode = encodingTree;
        }
    }

}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
    map<int, int> frequencyTable = buildFrequencyTable(input);
    HuffmanNode* encodingTree = buildEncodingTree(frequencyTable);
    map<int, string> encodingMap = buildEncodingMap(encodingTree);

    output.put('{');
    for(auto it = frequencyTable.begin(); it != frequencyTable.end(); ++it) {
        if (it != frequencyTable.begin()) {
            output.put(',');
            output.put(' ');
        }
        string character = to_string(it->first);
        for(unsigned i = 0; i < character.size(); ++i) {
            output.put(character[i]);
        }
        output.put(':');
        string frequency = to_string(it->second);
        for(unsigned i = 0; i < frequency.size(); ++i) {
            output.put(frequency[i]);
        }
    }
    output.put('}');
    input.clear();
    input.seekg(0, ios::beg);
    encodeData(input, encodingMap, output);
    freeTree(encodingTree);

}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
    if (node != nullptr) return;
    freeTree(node->zero);
    freeTree(node->one);
    delete node;
}
