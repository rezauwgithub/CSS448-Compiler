/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Token.cpp
 * Author: rezan
 * 
 * Created on April 4, 2017, 7:32 PM
 */

#include "Token.h"





Token::Token()
{
	this->tokenClass = ERROR;
	
	this->tokenLineNumber = 0;
	this->tokenColumnNumber = 0;        
        this->tokenPrecedence = -1;
//        this->tokenFamily = -1;
	
	// Initialize the tokenClassLookup vector.
	tokenClassLookup.push_back("ERROR");
	tokenClassLookup.push_back("BLOCK_COMMENT");
	tokenClassLookup.push_back("LINE_COMMENT");
	tokenClassLookup.push_back("OPERATOR_MINUS");
	tokenClassLookup.push_back("OPERATOR_EXCLAMATION_POINT");
	tokenClassLookup.push_back("OPERATOR_TILDE");
	tokenClassLookup.push_back("OPERATOR_ASTERISK");
	tokenClassLookup.push_back("OPERATOR_DIVISION");
	tokenClassLookup.push_back("OPERATOR_PLUS");
	tokenClassLookup.push_back("OPERATOR_DOT");
	tokenClassLookup.push_back("OPERATOR_ARROW");
	tokenClassLookup.push_back("OPERATOR_LEFT_SHIFT");
	tokenClassLookup.push_back("OPERATOR_RIGHT_SHIFT");
	tokenClassLookup.push_back("OPERATOR_LESS_THAN");
	tokenClassLookup.push_back("OPERATOR_LESS_OR_EQUAL");
	tokenClassLookup.push_back("OPERATOR_GREATER_THAN");
	tokenClassLookup.push_back("OPERATOR_GREATER_OR_EQUAL");
	tokenClassLookup.push_back("OPERATOR_COMPAREEQUAL");
	tokenClassLookup.push_back("OPERATOR_NOT_EQUAL");
	tokenClassLookup.push_back("OPERATOR_AMPERSAND");
	tokenClassLookup.push_back("OPERATOR_BITWISE_AND");
	tokenClassLookup.push_back("OPERATOR_BITWISE_OR");
	tokenClassLookup.push_back("OPERATOR_LOGICAL_AND");
	tokenClassLookup.push_back("OPERATOR_LOGICAL_OR");
	tokenClassLookup.push_back("OPERATOR_ASSIGNMENT");
	tokenClassLookup.push_back("IDENTIFIER");
	tokenClassLookup.push_back("CHARACTER_LITERAL");
	tokenClassLookup.push_back("INTEGER");
	tokenClassLookup.push_back("FLOAT_LEADING_DIGIT");
	tokenClassLookup.push_back("FLOAT_LEADING_DECIMAL");
	tokenClassLookup.push_back("FLOAT_NO_DECIMAL");
	tokenClassLookup.push_back("STRING_LITERAL");
	tokenClassLookup.push_back("LEFT_PAREN");
	tokenClassLookup.push_back("RIGHT_PAREN");
	tokenClassLookup.push_back("LEFT_BRACKET");
	tokenClassLookup.push_back("RIGHT_BRACKET");
	tokenClassLookup.push_back("LEFT_CURLY_BRACE");
	tokenClassLookup.push_back("RIGHT_CURLY_BRACE");
	tokenClassLookup.push_back("COMMA");
	tokenClassLookup.push_back("SEMICOLON");
	tokenClassLookup.push_back("WHITESPACE");
	tokenClassLookup.push_back("KEYWORD_BYTE");
	tokenClassLookup.push_back("KEYWORD_CONST");
	tokenClassLookup.push_back("KEYWORD_ELSE");
	tokenClassLookup.push_back("KEYWORD_END");
	tokenClassLookup.push_back("KEYWORD_EXIT");
	tokenClassLookup.push_back("KEYWORD_FLOAT64");
	tokenClassLookup.push_back("KEYWORD_FOR");
	tokenClassLookup.push_back("KEYWORD_FUNCTION");
	tokenClassLookup.push_back("KEYWORD_IF");
	tokenClassLookup.push_back("KEYWORD_INT32");
	tokenClassLookup.push_back("KEYWORD_PRINT");
	tokenClassLookup.push_back("KEYWORD_RECORD");
	tokenClassLookup.push_back("KEYWORD_REF");
	tokenClassLookup.push_back("KEYWORD_RETURN");
	tokenClassLookup.push_back("KEYWORD_STATIC");
	tokenClassLookup.push_back("KEYWORD_TYPE");
	tokenClassLookup.push_back("KEYWORD_VAR");
	tokenClassLookup.push_back("KEYWORD_WHILE");

}

Token::Token(const Token& orig) 
{
	tokenClass = orig.tokenClass;
//        tokenFamily = orig.tokenFamily;
	tokenChar = orig.tokenChar;

        tokenPrecedence = orig.tokenPrecedence;
        
	tokenLineNumber = orig.tokenLineNumber;
	tokenColumnNumber = orig.tokenColumnNumber;

	// Initialize the tokenClassLookup vector.
	tokenClassLookup = orig.tokenClassLookup;
}

Token::~Token() 
{
	
}

int Token::setTokenPrecedence(TokenClass tokenClass) {
    switch(tokenClass){            

        case OPERATOR_ASSIGNMENT:

            
            this->tokenPrecedence = 1;
            return 1;
            break;
            
        case LEFT_CURLY_BRACE:
        case RIGHT_CURLY_BRACE:
            
            this->tokenPrecedence = 2;
            return 2;
            break;
            
        case LEFT_BRACKET:
        case RIGHT_BRACKET:            
            
            this->tokenPrecedence = 3;
            return 3;
            break;
            
        case LEFT_PAREN:
        case RIGHT_PAREN:
            
            this->tokenPrecedence = 4;
            return 4;
            break;
            
        case OPERATOR_PLUS: 
        case OPERATOR_MINUS:
            
            this->tokenPrecedence = 5;
            return 5;
            break;
            
        case OPERATOR_ASTERISK:
        case OPERATOR_DIVISION:
            
            this->tokenPrecedence = 6;
            return 6;
            break;
            
        case OPERATOR_COMPAREEQUAL:
        case OPERATOR_NOT_EQUAL:
        case OPERATOR_AMPERSAND:
        case OPERATOR_BITWISE_AND:
        case OPERATOR_BITWISE_OR:
        case OPERATOR_LOGICAL_AND:
        case OPERATOR_LOGICAL_OR:
        case OPERATOR_LEFT_SHIFT:  //??????? WHAT IS THIS ????????//
        case OPERATOR_RIGHT_SHIFT:  //??????? WHAT IS THIS ????????//
        case OPERATOR_LESS_THAN:
        case OPERATOR_LESS_OR_EQUAL:
        case OPERATOR_GREATER_THAN:
        case OPERATOR_GREATER_OR_EQUAL:
        case OPERATOR_DOT:
        case OPERATOR_ARROW:
        case OPERATOR_EXCLAMATION_POINT:
        case OPERATOR_TILDE:
        //case OPERATOR_MINUS:  //Minus vs negative... how are you going to check?
                
                this->tokenPrecedence = 7;
                return 7;
                break;
                
        default:
                this->tokenPrecedence = 0;
                return 0;
                break;
             
    }
}

//void Token::setTokenFamily(Token tok){
//    switch(tok.getTokenClass())
//    {
//        case COMMA:
//	case SEMICOLON:
//	case WHITESPACE:
//	case KEYWORD_BYTE:
//	case KEYWORD_CONST:
//	case KEYWORD_ELSE:
//	case KEYWORD_END:
//	case KEYWORD_EXIT:
//	case KEYWORD_FLOAT64:
//	case KEYWORD_FOR:
//	case KEYWORD_FUNCTION:
//	case KEYWORD_IF:
//	case KEYWORD_INT32:
//	case KEYWORD_PRINT:
//	case KEYWORD_RECORD:
//	case KEYWORD_REF:
//	case KEYWORD_RETURN:
//	case KEYWORD_STATIC:
//	case KEYWORD_TYPE:
//	case KEYWORD_VAR:
//	case KEYWORD_WHILE:
//        case IDENTIFIER:
//	case CHARACTER_LITERAL:
//	case INTEGER:
//	case FLOAT_LEADING_DIGIT:
//	case FLOAT_LEADING_DECIMAL:
//	case FLOAT_NO_DECIMAL:
//	case STRING_LITERAL:
//            
//    }
//}


void Token::append(char toAppend) {
	tokenChar.push_back(toAppend);
}

int Token::getLineNumber() {
	return tokenLineNumber;
}
int Token::getColumnNumber() {
	return tokenColumnNumber;
}
void Token::setLineNumber(int line) {
	tokenLineNumber = line;
}
void Token::setColumnNumber(int column) {
	tokenColumnNumber = column;
}

int Token::getLength() {
	return tokenChar.size();
}

TokenClass Token::getTokenClass()
{
	return this->tokenClass;
}

int Token::getTokenClassInt()
{
	return static_cast<int>(this->tokenClass);
}

int Token::getPrecedence() {
    return this->tokenPrecedence;
}

void Token::setTokenClassAndPrecedenceAndFamily(TokenClass tokenClass)
{
	this->tokenClass = tokenClass;
        this->tokenPrecedence = setTokenPrecedence(tokenClass);
//        this->tokenFamily = set
}

bool Token::operator ==(const Token& other) const
{
    if(this->tokenClass == other.tokenClass)
        return true;
    else 
        return false;
}

bool Token::operator !=(const Token& other) const
{
    if(this->tokenClass != other.tokenClass)
        return true;
    else
        return false;
}

ostream& operator<<(ostream& output,  Token& thisToken) {
	
	output << "[" << thisToken.getLineNumber() << ", ";
	output << thisToken.getColumnNumber() << "] ";

	output << thisToken.getTokenClassChar();


	// print out the string matched for this token, if it's of an appropriate class
	switch (thisToken.getTokenClass()) {
	case ERROR:
	case BLOCK_COMMENT:
	case LINE_COMMENT:
	case IDENTIFIER:
	case CHARACTER_LITERAL:
	case INTEGER:
	case FLOAT_LEADING_DIGIT:
	case FLOAT_LEADING_DECIMAL:
	case FLOAT_NO_DECIMAL:
	case STRING_LITERAL:
		output << " (";

		//while (thisToken.tokenChar.size() > 0) {
		//	output << thisToken.tokenChar.front();
		//	thisToken.tokenChar.pop_front();
		//}

		output << thisToken.getTokenText();

		output << ")";
		break;
	default:
		break;
	}

	return output;
}

string Token::getTokenText() {
	std::string toReturn(this->tokenChar.begin(), this->tokenChar.end());
	return toReturn;
}


// return the current TokenClass, as a char[]
const char* Token::getTokenClassChar() {

	int index = this->getTokenClassInt();

	return tokenClassLookup[index];
	
}