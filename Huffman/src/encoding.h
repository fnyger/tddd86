/*
 * TDDD86 Huffman Encoding
 * This file declares the functions that you will need to write in this
 * assignment for your Huffman Encoder in huffmanencoding.cpp.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 */

#ifndef _encoding_h
#define _encoding_h

#include <iostream>
#include <string>
#include <map>
#include "bitstream.h"
#include "HuffmanNode.h"
using namespace std;

/*
 * See huffmanencoding.cpp for documentation of these functions
 * (which you are supposed to write, based on the spec).
 */

/*
 * Build frequency table of characters from input.
 */
map<int, int> buildFrequencyTable(istream& input);
/*
 * Builds encoding tree of characters from frequency table.
 */
HuffmanNode* buildEncodingTree(const map<int, int>& freqTable);
/*
 * Builds encoding map of characters from endocing tree.
 */
map<int, string> buildEncodingMap(HuffmanNode* encodingTree);
/*
 * Huffman encodes data from input stream to output bit stream.
 */
void encodeData(istream& input, const map<int, string>& encodingMap, obitstream& output);
/*
 * Huffman decodes data from input bit stream to output stream.
 */
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output);
/*
 * Huffman compresses data from input stream to output bit stream.
 */
void compress(istream& input, obitstream& output);
/*
 * Huffman decompresses data from input bit stream to output stream.
 */
void decompress(ibitstream& input, ostream& output);
/*
 * Frees tree by deleting all nodes on heap.
 */
void freeTree(HuffmanNode* node);

#endif
