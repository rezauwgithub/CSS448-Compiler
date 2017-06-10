/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Token.h
 * Author: rezan
 *
 * Created on April 4, 2017, 7:32 PM
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <istream>
#include <queue>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

enum TokenClass {
	ERROR = 0,
	BLOCK_COMMENT,
	LINE_COMMENT,
	OPERATOR_MINUS,
	OPERATOR_EXCLAMATION_POINT,
	OPERATOR_TILDE,
	OPERATOR_ASTERISK,
	OPERATOR_DIVISION,
	OPERATOR_PLUS,
        OPERATOR_DOT,
        OPERATOR_ARROW,
	OPERATOR_LEFT_SHIFT,
	OPERATOR_RIGHT_SHIFT,
	OPERATOR_LESS_THAN,
	OPERATOR_LESS_OR_EQUAL,
	OPERATOR_GREATER_THAN,
	OPERATOR_GREATER_OR_EQUAL,
	OPERATOR_COMPAREEQUAL,
	OPERATOR_NOT_EQUAL,
	OPERATOR_AMPERSAND,
	OPERATOR_BITWISE_AND,
	OPERATOR_BITWISE_OR,
	OPERATOR_LOGICAL_AND,
	OPERATOR_LOGICAL_OR,
	OPERATOR_ASSIGNMENT,
	IDENTIFIER,
	CHARACTER_LITERAL,
	INTEGER,
	FLOAT_LEADING_DIGIT,
	FLOAT_LEADING_DECIMAL,
	FLOAT_NO_DECIMAL,
	STRING_LITERAL,
	LEFT_PAREN,
	RIGHT_PAREN,
	LEFT_BRACKET,
	RIGHT_BRACKET,
	LEFT_CURLY_BRACE,
	RIGHT_CURLY_BRACE,
	COMMA,
	SEMICOLON,
	WHITESPACE,
	KEYWORD_BYTE,
	KEYWORD_CONST,
	KEYWORD_ELSE,
	KEYWORD_END,
	KEYWORD_EXIT,
	KEYWORD_FLOAT64,
	KEYWORD_FOR,
	KEYWORD_FUNCTION,
	KEYWORD_IF,
	KEYWORD_INT32,
	KEYWORD_PRINT,
	KEYWORD_RECORD,
	KEYWORD_REF,
	KEYWORD_RETURN,
	KEYWORD_STATIC,
	KEYWORD_TYPE,
	KEYWORD_VAR,
	KEYWORD_WHILE
};

enum TokenFamily {
    OPERATOR = 0,
    NON_OPERATOR
};

class Token {
    
    private:
        TokenClass tokenClass;
        TokenFamily tokenFamily;
        int tokenPrecedence;
        
        int tokenLineNumber;
        int tokenColumnNumber;
        vector<const char*> tokenClassLookup;

        int setTokenPrecedence(TokenClass);

		
		

    public:
        
        Token();
        Token(const Token& orig);
        virtual ~Token();
        
		std::deque<char> tokenChar;

		int getLineNumber();
		int getColumnNumber();
		void setLineNumber(int line);
		void setColumnNumber(int column);
                
                int getPrecedence();
                void setPrecedence(TokenClass);
        
		// Gets the TokenClass of Token
		TokenClass getTokenClass();

		// Get the TokenClass as a char[]
		const char* getTokenClassChar();

		int getTokenClassInt();

		// Sets the TokenClass of Token
		void setTokenClassAndPrecedenceAndFamily(TokenClass tokenKind);

		int getLength();

        //bool checkChar(char c);
         
        void append(char toAppend);
        
        
		// get the text stored within the token as a string
		string getTokenText();

        // Compares two tokens for equality
        bool operator ==(const Token& other) const;
        
        // Compares two tokens for inequality
        bool operator !=(const Token& other) const;

		friend ostream& operator<<(ostream& output, Token& thisToken);

};

#endif /* TOKEN_H */

