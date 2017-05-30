/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lexer.h
 * Author: Daniel --
 *
 * Created on April 11, 2017, 8:35 AM
 */

#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <iostream>
#include <string>

#include <vector>
#include <deque>

#include "Token.h"

class Lexer
{
public:
    Lexer(const char* fileName);
    bool getNextChar(char& current); // write the next char into current. Return false if EOF
	bool backUp1Char();
    std::vector<Token> tokens;
	Token createNextToken();
	std::vector<Token> getTokens();

private:

	const static std::string reservedWords[]; 
	const static int reservedWordsLength;

	int currentLineNumber;
	int currentColumnNumber;

	std::deque<int> previousColumnNumbers;

	std::deque<char> buffer;
	int bufferIndex; // index of the next character that getNextChar() should return.

    std::ifstream file;
    std::string myString;
    bool tokenize();
};



#endif /* LEXER_H */
