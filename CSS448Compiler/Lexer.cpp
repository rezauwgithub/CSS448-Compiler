/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Lexer.cpp
* Author: Daniel
*
* Created on April 11, 2017, 8:35 AM
*/

#include "Lexer.h"
#include <string>


using namespace std;

const int Lexer::reservedWordsLength = 18;
const std::string Lexer::reservedWords[] = {
	"byte",
	"const",
	"else",
	"end",
	"exit",
	"float64",
	"for",
	"function",
	"if",
	"int32",
	"print",
	"record",
	"ref",
	"return",
	"static",
	"type",
	"var",
	"while" };

Lexer::Lexer(const char* filePath)
{
	// Line and column numbers do not begin at zero, they begin at 1.
	currentLineNumber = 1;
	currentColumnNumber = 1;

	try   //If file opens, tokenize 
        {

		file.open(filePath); //open for reading


		//// debugging info:
		//cout << "true: " << true << endl;
		//cout << "false: " << false << endl;
		//cout << "file open: " << file.is_open() << endl;
		//cout << "file isgood: " << file.good() << endl;


		bufferIndex = 0;

		tokenize();
	}
	catch (exception e)
	{
		cerr << "READ FILE ERROR: " << e.what() << endl;
	}

	file.close();
}

bool Lexer::tokenize()
{
	//Daniel M's switch statement code (which calls getNextChar())
	//Creates all tokens and populates token queue

	while (!file.eof()) {
		// save the line and column number of the start of the token
		int line = currentLineNumber;
		int column = currentColumnNumber;
		
		Token curToken = createNextToken();
		curToken.setLineNumber(line);
		curToken.setColumnNumber(column);

		// createNextToken does not check if something is a keyword or not.
		// Check if the current token is actually a keyword
		if (curToken.getTokenClass() == IDENTIFIER) {

			for (int i = 0; i < Lexer::reservedWordsLength; i++){

				if (curToken.tokenChar.size() == Lexer::reservedWords[i].length()) {
					
					bool stringsMatch = true;
					for (int j = 0; j < curToken.tokenChar.size(); j++) {
						if (curToken.tokenChar[j] != Lexer::reservedWords[i][j]) {
							stringsMatch = false;
							break;
						}
					}

					if (stringsMatch) {
						// the current token string is equal to the current keyword

						// set the current token's token class appropriately.
						TokenClass nextTokenClass = IDENTIFIER;
						switch (i) {
						case 0: //	"byte"
							nextTokenClass = KEYWORD_BYTE;
							break;
						case 1: //	"const"
							nextTokenClass = KEYWORD_CONST;
							break;
						case 2: //	"else"
							nextTokenClass = KEYWORD_ELSE;
							break;
						case 3: //	"end"
							nextTokenClass = KEYWORD_END;
							break;
						case 4: //	"exit"
							nextTokenClass = KEYWORD_EXIT;
							break;
						case 5: //	"float64"
							nextTokenClass = KEYWORD_FLOAT64;
							break;
						case 6: //	"for"
							nextTokenClass = KEYWORD_FOR;
							break;
						case 7: //	"function"
							nextTokenClass = KEYWORD_FUNCTION;
							break;
						case 8: //	"if"
							nextTokenClass = KEYWORD_IF;
							break;
						case 9: //	"int32"
							nextTokenClass = KEYWORD_INT32;
							break;
						case 10: //	"print"
							nextTokenClass = KEYWORD_PRINT;
							break;
						case 11: //	"record"
							nextTokenClass = KEYWORD_RECORD;
							break;
						case 12: //	"ref"
							nextTokenClass = KEYWORD_REF;
							break;
						case 13: //	"return"
							nextTokenClass = KEYWORD_RETURN;
							break;
						case 14: //	"static"
							nextTokenClass = KEYWORD_STATIC;
							break;
						case 15: //	"type"
							nextTokenClass = KEYWORD_TYPE;
							break;
						case 16: //	"var"
							nextTokenClass = KEYWORD_VAR;
							break;
						case 17: //	"while"
							nextTokenClass = KEYWORD_WHILE;
							break;
						default:
							break;
						}

						curToken.setTokenClassAndPrecedenceAndFamily(nextTokenClass);
						break;
					}					
				}
			}
		}

		tokens.push(curToken);

		// Erase the token's characters from the buffer.
		buffer.erase(buffer.begin(), buffer.begin() + curToken.getLength());
		// set the buffer index back to the beginning
		bufferIndex = 0;

		// Since the previous token may not have used up all the
		// characters it read in, set the current line and
		// column numbers correctly.
		//TODO: add the code for reseting to correct line/column number

		std::deque<char>::iterator cur = buffer.end();
		while (cur > buffer.begin()) {
			cur--;
			
			// as we walk the string backwards, look for either the sequence "\n\r", or
			// for the single characters '\r' or '\n' in order to decrement the line number
			// and pop the previous column number off the stack.
			// else, decrement the column counter.
			switch (*cur){
			case '\r':
				currentLineNumber--;
				currentColumnNumber = previousColumnNumbers.back();
				previousColumnNumbers.pop_back();
				break;
			case '\n':

				// check for "\n\r" sequence (as we walk backwards)
				if (cur > buffer.begin()) {
					cur--;
					switch (*cur) {
					case '\r':
						currentLineNumber--;
						currentColumnNumber = previousColumnNumbers.back();
						previousColumnNumbers.pop_back();
						break;
					default:
						currentColumnNumber--;
						break;
					}
				}
				else {
					currentLineNumber--;
					currentColumnNumber = previousColumnNumbers.back();
					previousColumnNumbers.pop_back();
				}
				break;
			default:
				currentColumnNumber--;
				break;
			}
		}
		if (curToken.getLength() == 1) {
			currentColumnNumber++;
		}
	}

	while (tokens.size() > 0) {
		Token t = tokens.front();

		// do not print WHITESPACE, BLOCK_COMMENT or LINE_COMMENT tokens.
		switch (t.getTokenClass()) {
		case WHITESPACE:
		case BLOCK_COMMENT:
		case LINE_COMMENT:
			//cout << t << endl; // for debugging only
			break;
		default:
			cout << t << " Operation Precedence: " << t.getPrecedence() << endl;
			break;
		}
		tokens.pop();
	}

	return true;
}

bool Lexer::getNextChar(char& current)
{
	//cout << "getNextChar()" << endl;

	if (bufferIndex < buffer.size()) {
		current = buffer[bufferIndex];
		bufferIndex++;
		return true;
	}

	char nextChar;
	file.get(nextChar);

	//cout << nextChar << endl;

	if (!file.eof())
	{
		// Increment the line count when we we '\r', '\n', or the sequence "\r\n".
		// For any other character that we see, do not incremement the line count, but
		// _do_ increment the column count.
		// TODO: there are some zero-width characters that don't cause a line break, but don't
		//  take up column space, either. In the future we may check for those.
		//
		// Note, every time we increment the line counter, we also push the current column
		// counter onto a stack before we reset it to zero. This is done because in the
		// switch statement of createNextToken, we sometimes use a small a amount of
		// backtracking (usually 1-2 characters) in order to simplify the logic.
		// If we ever have to backtrack after having read in a newline character,
		// we will need to restore the previous column counter, which would have been reset
		// when we read in the newline.
		// The tokenize method will manage this stack after getNextChar populates it.
		switch (nextChar) {
		case '\r':
			currentLineNumber++;
			previousColumnNumbers.push_back(currentColumnNumber);
			currentColumnNumber = 1;
			break;
		case '\n':
			// check for "\r\n".
			if (current == '\r') {
				// don't update the line count _or_ the column count.
				break;
			}
			else {
				currentLineNumber++;
				previousColumnNumbers.push_back(currentColumnNumber);
				currentColumnNumber = 1;
			}
			break;
		default:
			currentColumnNumber++;
			break;
		}

		buffer.push_back(nextChar);
		bufferIndex++;
		current = nextChar;
		return true;
	}
	else
	{
		return false;
	}
}

bool Lexer::backUp1Char() {
	if (bufferIndex > 0){
		bufferIndex--;
		return true;
	}
	else {
		return false;
	}
}

Token Lexer::createNextToken() {
	Token myToken;

	char current = -1;
	getNextChar(current);
	switch (current) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		// error

		myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
		myToken.append(current);
		return myToken;

		break;
	case '\t':
	case '\n':
	case '\v':
	case '\f':
	case '\r':
	case ' ': // "space" character

		// whitespace
		myToken.setTokenClassAndPrecedenceAndFamily(WHITESPACE);

		// append the current character to the token string
		myToken.append(current);

		while (getNextChar(current)) {
			switch (current) {

			case '\t':
			case '\n':
			case '\v':
			case '\f':
			case '\r':
			case ' ':

				// append the current character to the token string
				myToken.append(current);
				break;
			default:

				return myToken;
				break;
			}
		}
		return myToken;
		break;
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
		// error

		myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
		myToken.append(current);
		return myToken;

		break;
	case '!':
		// operator_!

		myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_EXCLAMATION_POINT);
		myToken.append(current);
		return myToken;

		break;
	case '"':
		// string_literal
		// error

		myToken.setTokenClassAndPrecedenceAndFamily(STRING_LITERAL);
		myToken.append(current);

		while (getNextChar(current)) {
			// TODO: This is not the correct regex for a string literal
			switch (current) {
			case '"':
				myToken.append(current);
				return myToken;
				break;
			default:
				myToken.append(current);
				break;
			}
		}

		break;
	case '#':
	case '$':
	case '%':
		// error

		myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
		myToken.append(current);
		return myToken;

		break;
	case '&':
		// operator_&&
		// operator_&

		myToken.append(current);
		getNextChar(current);

		switch (current) {
		case '&':
			myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_LOGICAL_AND);
			myToken.append(current);
			return myToken;
			break;
		default:
			myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_BITWISE_AND);
			return myToken;
			break;
		}


		break;
	case '\'':
		// character_literal
		// error

		myToken.setTokenClassAndPrecedenceAndFamily(CHARACTER_LITERAL);
		myToken.append(current);

		while (getNextChar(current)) {
			// TODO: This is not the correct regex for a character literal
			switch (current) {
			case '\'':
				myToken.append(current);
				return myToken;
				break;
			default:
				myToken.append(current);
				break;
			}
		}

		break;
	case '(':
		// left_paren

		myToken.setTokenClassAndPrecedenceAndFamily(LEFT_PAREN);
		myToken.append(current);
		return myToken;

		break;
	case ')':
		// right_paren

		myToken.setTokenClassAndPrecedenceAndFamily(RIGHT_PAREN);
		myToken.append(current);
		return myToken;

		break;
	case '*':
		// operator_*

		myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_ASTERISK);
		myToken.append(current);
		return myToken;

		break;
	case '+':
		// operator_+

		myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_PLUS);
		myToken.append(current);
		return myToken;

		break;
	case ',':
		// comma

		myToken.setTokenClassAndPrecedenceAndFamily(COMMA);
		myToken.append(current);
		return myToken;

		break;
	case '-':
		// operator_-
		// integer
		// float_leading_digit
		// float_leading_decimal
		// float_no_decimal
		// error

		myToken.append(current);

		while (getNextChar(current)){
			switch (current) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				// integer
				// float_leading_digit
				// float_no_decimal


				myToken.append(current);

				while (getNextChar(current)) {
					switch (current) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						myToken.append(current);
						break;
					case '.':
						// float_leading_digit
						myToken.setTokenClassAndPrecedenceAndFamily(FLOAT_LEADING_DIGIT);

						myToken.append(current);
						while (getNextChar(current)) {
							switch (current) {
							case '0':
							case '1':
							case '2':
							case '3':
							case '4':
							case '5':
							case '6':
							case '7':
							case '8':
							case '9':
								myToken.append(current);
								break;
							case 'e':
								myToken.append(current);
								while (getNextChar(current)) {
									switch (current) {
									case '0':
									case '1':
									case '2':
									case '3':
									case '4':
									case '5':
									case '6':
									case '7':
									case '8':
									case '9':
										myToken.append(current);
										break;
									default:
										// if we see an "e", and it is NOT followed by another number, then this really
										// was not a FLOAT_LEADING_DIGIT. This was an integer, and "e" begins a new token.
										myToken.setTokenClassAndPrecedenceAndFamily(INTEGER);
										backUp1Char();
										return myToken;
										break;
									}
								}
								// if "e" is followed by the end of the file, then this token is an integer, and "e"
								// is a 1-character-long token right at the end of the file.
								myToken.setTokenClassAndPrecedenceAndFamily(INTEGER);
								backUp1Char();
								return myToken;
								break;
							default:
								return myToken;
								break;
							}
						}
						// we reached the end if file
						return myToken;
						break;
					case 'e':
						// float_no_decimal
						myToken.setTokenClassAndPrecedenceAndFamily(FLOAT_NO_DECIMAL);
						myToken.append(current);

						if (!getNextChar(current)) {
							// if "e" is followed by the end of the file, then this was actually an integer.
							return myToken;
						}
						else {
							// if there _is_ a next character, then back up 1 character so it can be
							// examined in the while loop.
							backUp1Char();
						}

						while (getNextChar(current)) {
							switch (current) {
							case '0':
							case '1':
							case '2':
							case '3':
							case '4':
							case '5':
							case '6':
							case '7':
							case '8':
							case '9':
								myToken.append(current);
								break;
							default:
								return myToken;
								break;
							}
						}
						return myToken;
						break;
					default:
						// integer
						myToken.setTokenClassAndPrecedenceAndFamily(INTEGER);
						return myToken;
						break;
					}
				}
				// integer
				myToken.setTokenClassAndPrecedenceAndFamily(INTEGER);
				return myToken;
				break;
			case '.':
				// float_leading_decimal
				// error


				// if the character immediately following the decimal place is a digit, then this is a float. Else, it's an error.
				myToken.append(current);
				if (getNextChar(current)) {
					switch (current) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						myToken.setTokenClassAndPrecedenceAndFamily(FLOAT_LEADING_DECIMAL);
						myToken.append(current);

						// now that we know this is a float, keep building the token.
						while (getNextChar(current)) {
							switch (current) {
							case '0':
							case '1':
							case '2':
							case '3':
							case '4':
							case '5':
							case '6':
							case '7':
							case '8':
							case '9':
								myToken.append(current);
								break;
							case 'e':
								myToken.append(current);

								if (!getNextChar(current)) {
									// if "e" is followed by the end of the file, then "e" is not actually part of the float.
									return myToken;
								}
								else {
									// if there _is_ a next character, then back up 1 character so it can be
									// examined in the while loop.
									backUp1Char();
								}

								while (getNextChar(current)) {
									switch (current) {
									case '0':
									case '1':
									case '2':
									case '3':
									case '4':
									case '5':
									case '6':
									case '7':
									case '8':
									case '9':
										myToken.append(current);
										break;
									default:
										return myToken;
										break;
									}
								}
								return myToken;
								break;
							default:
								return myToken;
								break;
							}
						}
						// if we reach the end of file, this is still a float.
						return myToken;
						break;
					default:
						myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
						return myToken;
						break;
					}
				}
				else {
					// There was no next character after the decimal.
					//  This is an error.
					myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
					return myToken;
				}
				break;
			default:
				// operator_-
				myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_MINUS);
				return myToken;
				break;
			}
		}
		// operator_-
		myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_MINUS);
		return myToken;
		break;
	case '.':
		// float_leading_decimal
		// error


		// if the character immediately following the decimal place is a digit, then this is a float. Else, it's an error.
		myToken.append(current);
		if (getNextChar(current)) {
			switch (current) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				myToken.setTokenClassAndPrecedenceAndFamily(FLOAT_LEADING_DECIMAL);
				myToken.append(current);

				// now that we know this is a float, keep building the token.
				while (getNextChar(current)) {
					switch (current) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						myToken.append(current);
						break;
					case 'e':
						myToken.append(current);

						if (!getNextChar(current)) {
							// if "e" is followed by the end of the file, then "e" is not actually part of the float.
							return myToken;
						}
						else {
							// if there _is_ a next character, then back up 1 character so it can be
							// examined in the while loop.
							backUp1Char();
						}

						while (getNextChar(current)) {
							switch (current) {
							case '0':
							case '1':
							case '2':
							case '3':
							case '4':
							case '5':
							case '6':
							case '7':
							case '8':
							case '9':
								myToken.append(current);
								break;
							default:
								return myToken;
								break;
							}
						}
						return myToken;
						break;
					default:
						return myToken;
						break;
					}
				}
				// if we reach the end of file, this is still a float.
				return myToken;
				break;
			default:
				myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
				return myToken;
				break;
			}
		}
		else {
			// There was no next character after the decimal.
			//  This is an error.
			myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
			return myToken;
		}

		break;
	case '/':
		// /*_comment
		// //_comment
		// operator_/

		myToken.append(current);
		getNextChar(current);
		switch (current) {
		case '*':
			// /*_comment
			myToken.setTokenClassAndPrecedenceAndFamily(BLOCK_COMMENT);
			myToken.append(current);

			while (getNextChar(current)) {
				switch (current) {
				case '*': // search for "*/" to end the comment.
					myToken.append(current);
					getNextChar(current);
					if (current == '/') { // we see the "*/" that ends the block comment.
						myToken.append(current);
						return myToken;
					}
					else {
						backUp1Char();
					}
					break;
				default:
					myToken.append(current);
					break;
				}
			}
			// we reached the end of the file, and have an unclosed comment.
			// TODO: Add an error message that says "Unexpected end of file found in block comment."
			myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
			return myToken;
			break;

		case '/':
			// //_comment
			myToken.append(current);
			myToken.setTokenClassAndPrecedenceAndFamily(LINE_COMMENT);

			// continue appending to the comment until we reach a newline character.
			while (getNextChar(current)) {
				switch (current) {
				case '\n':
					return myToken;
					break;
				default:
					myToken.append(current);
					break;
				}
			}
			// if we reach the end of the file without seeing a newline character,
			// that's fine. The comment ends at the end of file.
			// This case would occur when we have a //_comment in the last line of a file.
			return myToken;
			break;

		default:
			// operator_/
			myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_DIVISION);
			return myToken;
		}
		break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		// integer
		// float_leading_digit
		// float_no_decimal


		myToken.append(current);

		while (getNextChar(current)) {
			switch (current) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				myToken.append(current);
				break;
			case '.':
				// float_leading_digit
				myToken.setTokenClassAndPrecedenceAndFamily(FLOAT_LEADING_DIGIT);

				myToken.append(current);
				while (getNextChar(current)) {
					switch (current) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						myToken.append(current);
						break;
					case 'e':
						myToken.append(current);
						while (getNextChar(current)) {
							switch (current) {
							case '0':
							case '1':
							case '2':
							case '3':
							case '4':
							case '5':
							case '6':
							case '7':
							case '8':
							case '9':
								myToken.append(current);
								break;
							default:
								// if we see an "e", and it is NOT followed by another number, then this really
								// was not a FLOAT_LEADING_DIGIT. This was an integer, and "e" begins a new token.
								myToken.setTokenClassAndPrecedenceAndFamily(INTEGER);
								backUp1Char();
								return myToken;
								break;
							}
						}
						// if "e" is followed by the end of the file, then this token is an integer, and "e"
						// is a 1-character-long token right at the end of the file.
						myToken.setTokenClassAndPrecedenceAndFamily(INTEGER);
						backUp1Char();
						return myToken;
						break;
					default:
						return myToken;
						break;
					}
				}
				// we reached the end if file
				return myToken;
				break;
			case 'e':
				// float_no_decimal
				myToken.setTokenClassAndPrecedenceAndFamily(FLOAT_NO_DECIMAL);
				myToken.append(current);

				if (!getNextChar(current)) {
					// if "e" is followed by the end of the file, then this was actually an integer.
					return myToken;
				}
				else {
					// if there _is_ a next character, then back up 1 character so it can be
					// examined in the while loop.
					backUp1Char();
				}

				while (getNextChar(current)) {
					switch (current) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						myToken.append(current);
						break;
					default:
						return myToken;
						break;
					}
				}
				return myToken;
				break;
			default:
				// integer
				myToken.setTokenClassAndPrecedenceAndFamily(INTEGER);
				return myToken;
				break;
			}
		}
		// integer
		myToken.setTokenClassAndPrecedenceAndFamily(INTEGER);
		return myToken;
		break;
	case ':':
		// error

		myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
		myToken.append(current);
		return myToken;

		break;
	case ';':
		// semicolon

		myToken.setTokenClassAndPrecedenceAndFamily(SEMICOLON);
		myToken.append(current);
		return myToken;

		break;
	case '<':
		// operator_<<
		// operator_<=
		// operator_<

		myToken.append(current);
		getNextChar(current);
		switch (current) {
		case '<':
			myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_LEFT_SHIFT);
			myToken.append(current);
			return myToken;
			break;
		case '=':
			myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_LESS_OR_EQUAL);
			myToken.append(current);
			return myToken;
			break;
		default:
			myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_LESS_THAN);
			return myToken;
		}

		break;

	case '=':
		myToken.append(current);

		if (getNextChar(current)) {
			switch (current) {
			case '=':
				// operator_==

				myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_EQUAL);
				myToken.append(current);
				break;
			default:
				myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_ASSIGNMENT);
				return myToken;
				break;
			}
		}

		myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_ASSIGNMENT);
		return myToken;
		break;

	case '>':
		// operator_>>
		// operator_>=
		// operator_>

		myToken.append(current);
		getNextChar(current);
		switch (current) {
		case '>':
			myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_RIGHT_SHIFT);
			myToken.append(current);
			return myToken;
			break;
		case '=':
			myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_GREATER_OR_EQUAL);
			myToken.append(current);
			return myToken;
			break;
		default:
			myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_GREATER_THAN);
			return myToken;
		}

		break;
	case '?':
	case '@':
		// error

		myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
		myToken.append(current);
		return myToken;

		break;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
		// identifier
		myToken.setTokenClassAndPrecedenceAndFamily(IDENTIFIER);
		myToken.append(current);

		while (getNextChar(current)) {
			switch (current) {
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z':
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '_':

				myToken.append(current);
				break;
			default:
				return myToken;
				break;
			}
		}

		break;
	case '[':
		// left_bracket

		myToken.setTokenClassAndPrecedenceAndFamily(LEFT_BRACKET);
		myToken.append(current);
		return myToken;

		break;
	case '\\':
		// error

		myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
		myToken.append(current);
		return myToken;

		break;
	case ']':
		// right_bracket

		myToken.setTokenClassAndPrecedenceAndFamily(RIGHT_BRACKET);
		myToken.append(current);
		return myToken;

		break;
	case '^':
		// operator_^

		myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_BITWISE_AND);
		myToken.append(current);
		return myToken;

		break;
	case '_':
	case '`':
		// error

		myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
		myToken.append(current);
		return myToken;

		break;

	case '{':
		// left_curly_brace

		myToken.setTokenClassAndPrecedenceAndFamily(LEFT_CURLY_BRACE);
		myToken.append(current);
		return myToken;

		break;
	case '|':
		// operator_||
		// operator_|

		myToken.append(current);
		getNextChar(current);
		switch (current) {
		case '|':
			myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_LOGICAL_OR);
			myToken.append(current);
			return myToken;
			break;
		default:
			myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_BITWISE_OR);
			myToken.append(current);
			return myToken;
			break;
		}

		break;
	case '}':
		// right_curly_brace

		myToken.setTokenClassAndPrecedenceAndFamily(RIGHT_CURLY_BRACE);
		myToken.append(current);
		return myToken;

		break;
	case '~':
		// operator_~

		myToken.setTokenClassAndPrecedenceAndFamily(OPERATOR_TILDE);
		myToken.append(current);
		return myToken;

		break;
	case 127:
		// error

		myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
		myToken.append(current);
		return myToken;

		break;
	default:
		// error

		myToken.setTokenClassAndPrecedenceAndFamily(ERROR);
		myToken.append(current);
		return myToken;

		break;
	}
}