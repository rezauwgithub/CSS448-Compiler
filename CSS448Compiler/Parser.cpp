/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Parser.cpp
* Author: Daniel
*
* Created on May 16, 2017, 2:58 PM
*/

#include "Parser.h"

using namespace std;

Parser::Parser() {
}

Node* Parser::getASTroot(){
	return parseTreeRoot;
}

void Parser::parseTokens(std::vector<Token> tokens) {
	readInTokens(tokens);
	nextToken = this->tokens.begin();

	parseTreeRoot = new ExpressionNode("Root");

	Program(parseTreeRoot);


}

void Parser::readInTokens(std::vector<Token> tokens) {
	this->tokens = tokens;
}

void Parser::printTree() {

	cout << "---- Print Tree ----" << endl;
	parseTreeRoot->printSubtree(0);
	cout << endl;
	cout << "---- Done ----" << endl;

}

Node* Parser::copyTree() {
	if (parseTreeRoot == NULL) {
		return NULL;
	}
	return parseTreeRoot->copySubtree();
}

bool Parser::match(Node* Parent, TokenClass nextGrammarElementTokenClass) {

	//Token temp;
	//temp.setTokenClassAndPrecedenceAndFamily(nextGrammarElementTokenClass);

	//ExpressionNode* cur = new ExpressionNode(temp.getTokenClassChar());
	//Parent->children.push_back(cur);
	// printTree();


	Node* cur = Parent;

	TokenClass nextTokenClass = nextToken->getTokenClass();

	//Check if next token's class == token class of next item in grammar
	if (nextTokenClass == nextGrammarElementTokenClass) {
		TokenNode* toAdd = new TokenNode(*nextToken);
		Parent->children.push_back(toAdd);
		nextToken++;
		return (true) ||
			(cur->deleteChildren());
	}
	else
		return (false) ||
		(cur->deleteChildren());
}


bool Parser::Program(Node* Parent){

	ExpressionNode* cur = new ExpressionNode("Program");
	Parent->children.push_back(cur);

	// printTree();


	// printTree();

	return (Statements(cur)) ||
		(cur->deleteChildren());
}


bool Parser::Statements(Node* Parent)
{
	// printTree();

	ExpressionNode* cur = new ExpressionNode("Statements");
	Parent->children.push_back(cur);

	// printTree();



	if (nextToken != tokens.end()) {
		return (Statements_1(cur) || true) ||
			(cur->deleteChildren());
	}
	else {
		return (Statements_END(cur)) ||
			(cur->deleteChildren());
	}
}

bool Parser::Statements_1(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Statements_1");
	Parent->children.push_back(cur);

	// printTree();


	return (Statement(cur) &&
		Statements(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Statements_END(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Statements_END");
	Parent->children.push_back(cur);

	// printTree();


	return true;
}

bool Parser::Statement(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Statement");
	Parent->children.push_back(cur);

	// printTree();


	switch (nextToken->getTokenClass()){
	case(KEYWORD_TYPE) :
	case(KEYWORD_FUNCTION) :
	case(KEYWORD_STATIC) :
	case(KEYWORD_CONST) :
	case(KEYWORD_VAR) :
					  return (Declaration_Statement(cur)) ||
					  (cur->deleteChildren());

	case(LEFT_CURLY_BRACE) :
		return (Block_Statement(cur)) ||
		(cur->deleteChildren());

	case(KEYWORD_FOR) :
		return (For_Statement(cur)) ||
		(cur->deleteChildren());

	case(KEYWORD_WHILE) :
		return (While_Statement(cur)) ||
		(cur->deleteChildren());

	case(KEYWORD_IF) :
		return (If_Statement(cur)) ||
		(cur->deleteChildren());

	case(KEYWORD_PRINT) :
		return (Print_Statement(cur)) ||
		(cur->deleteChildren());

	case(KEYWORD_RETURN) :
		return (Return_Statement(cur)) ||
		(cur->deleteChildren());

	case(KEYWORD_EXIT) :
		return (Exit_Statement(cur)) ||
		(cur->deleteChildren());

		//Check logic for this case
	default:
		return (Expression_Statement(cur)) ||
			(cur->deleteChildren());
	}
}

bool Parser::Declaration_Statement(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Declaration_Statement");
	Parent->children.push_back(cur);

	// printTree();


	switch (nextToken->getTokenClass()){
	case(KEYWORD_TYPE) :
		return (Type_Declaration(cur)) ||
		(cur->deleteChildren());

	case(KEYWORD_FUNCTION) :
		return (Function_Declaration(cur)) ||
		(cur->deleteChildren());

	case(KEYWORD_STATIC) :
	case(KEYWORD_CONST) :
	case(KEYWORD_VAR) :
					  return (Variable_Declaration(cur)) ||
					  (cur->deleteChildren());
	}
}

bool Parser::Type_Declaration(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Type_Declaration");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_TYPE) &&
		match(cur, IDENTIFIER) &&
		Type_Descriptor(cur) &&
		match(cur, SEMICOLON)) ||
		(cur->deleteChildren());
}

bool Parser::Type_Descriptor(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Type_Descriptor");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;

	return ((nextToken = save, (cur->deleteChildren() || (Type_Descriptor_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Type_Descriptor_2(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::Type_Descriptor_1(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Type_Descriptor_1");
	Parent->children.push_back(cur);

	// printTree();


	return (Non_Array_Type_Descriptor(cur) &&
		Dimension(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Type_Descriptor_2(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Type_Descriptor_2");
	Parent->children.push_back(cur);

	// printTree();


	return (Non_Array_Type_Descriptor(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Non_Array_Type_Descriptor(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Non_Array_Type_Descriptor");
	Parent->children.push_back(cur);

	// printTree();


	switch (nextToken->getTokenClass()){
	case(KEYWORD_RECORD) :
		return (Record_Descriptor(cur)) ||
		(cur->deleteChildren());

	case(IDENTIFIER) :
		return (match(cur, IDENTIFIER)) ||
		(cur->deleteChildren());

	case(KEYWORD_BYTE) :
	case(KEYWORD_INT32) :
	case(KEYWORD_FLOAT64) :
						  return (Basic_Type(cur)) ||
						  (cur->deleteChildren());
	}
}

bool Parser::Record_Descriptor(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Record_Descriptor");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_RECORD) &&
		Field_Declarations(cur) &&
		match(cur, KEYWORD_END)) ||
		(cur->deleteChildren());
}


bool Parser::Field_Declarations(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Field_Declarations");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;

	return ((nextToken = save, (cur->deleteChildren() || (Field_Declarations_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Field_Declarations_2(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Field_Declarations_3(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::Field_Declarations_1(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Field_Declarations_1");
	Parent->children.push_back(cur);

	// printTree();


	return (Field_Declaration(cur) && Field_Declarations(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Field_Declarations_2(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Field_Declarations_2");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, COMMA) && Field_Declarations(cur)) ||
		(cur->deleteChildren());
}
bool Parser::Field_Declarations_3(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Field_Declarations_3");
	Parent->children.push_back(cur);

	// printTree();


	return (true) ||
		(cur->deleteChildren());
}

bool Parser::Field_Declaration(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Field_Declaration");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, IDENTIFIER) &&
		Type_Descriptor(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Basic_Type(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Basic_Type");
	Parent->children.push_back(cur);

	// printTree();


	switch (nextToken->getTokenClass()){
	case(KEYWORD_BYTE) :
		return (match(cur, KEYWORD_BYTE)) ||
		(cur->deleteChildren());
	case(KEYWORD_INT32) :
		return (match(cur, KEYWORD_INT32)) ||
		(cur->deleteChildren());
	case(KEYWORD_FLOAT64) :
		return (match(cur, KEYWORD_FLOAT64)) ||
		(cur->deleteChildren());
	}
}

bool Parser::Dimension(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Dimension");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, LEFT_BRACKET) &&
		Expression(cur) &&
		match(cur, RIGHT_BRACKET)) ||
		(cur->deleteChildren());
}

bool Parser::Function_Declaration(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Function_Declaration");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return (
		(nextToken = save, (cur->deleteChildren() || (Function_Declaration_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Function_Declaration_2(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Function_Declaration_3(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::Function_Declaration_1(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Function_Declaration_1");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_FUNCTION) &&
		match(cur, IDENTIFIER) &&
		match(cur, LEFT_PAREN) &&
		match(cur, RIGHT_PAREN) &&
		Block_Statement(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Function_Declaration_2(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Function_Declaration_2");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_FUNCTION) &&
		match(cur, IDENTIFIER) &&
		match(cur, LEFT_PAREN) &&
		Parameters(cur) &&
		match(cur, RIGHT_PAREN) &&
		Block_Statement(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Function_Declaration_3(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Function_Declaration_3");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_FUNCTION) &&
		match(cur, IDENTIFIER) &&
		match(cur, LEFT_PAREN) &&
		Parameters(cur) &&
		match(cur, RIGHT_PAREN) &&
		Type_Descriptor(cur) &&
		Block_Statement(cur)) ||
		(cur->deleteChildren());
}


bool Parser::Parameters(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Parameters");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (Parameters_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Parameters_2(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Parameters_3(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::Parameters_1(Node* Parent){

	ExpressionNode* cur = new ExpressionNode("Parameters_1");
	Parent->children.push_back(cur);

	// printTree();


	return (Parameter(cur) && Parameters(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Parameters_2(Node* Parent){

	ExpressionNode* cur = new ExpressionNode("Parameters_2");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, COMMA) && Parameters_1(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Parameters_3(Node* Parent){

	ExpressionNode* cur = new ExpressionNode("Parameters_3");
	Parent->children.push_back(cur);

	// printTree();


	return (true) ||
		(cur->deleteChildren());
}

bool Parser::Parameter(Node* Parent){

	ExpressionNode* cur = new ExpressionNode("Parameter");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (Parameter_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Parameter_2(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Parameter_3(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Parameter_4(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Parameter_5(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::Parameter_1(Node* Parent){

	ExpressionNode* cur = new ExpressionNode("Parameter_1");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_REF) &&
		match(cur, KEYWORD_CONST) &&
		match(cur, IDENTIFIER) &&
		Non_Array_Type_Descriptor(cur) &&
		Dimension_Wildcards(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Parameter_2(Node* Parent){

	ExpressionNode* cur = new ExpressionNode("Parameter_2");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_CONST) &&
		match(cur, IDENTIFIER) &&
		Non_Array_Type_Descriptor(cur) &&
		Dimension_Wildcards(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Parameter_3(Node* Parent){

	ExpressionNode* cur = new ExpressionNode("Parameter_3");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, IDENTIFIER) &&
		Non_Array_Type_Descriptor(cur) &&
		Dimension_Wildcards(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Parameter_4(Node* Parent){

	ExpressionNode* cur = new ExpressionNode("Parameter_4");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, IDENTIFIER) &&
		Non_Array_Type_Descriptor(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Parameter_5(Node* Parent){

	ExpressionNode* cur = new ExpressionNode("Parameter_5");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_REF) &&
		match(cur, KEYWORD_CONST) &&
		match(cur, IDENTIFIER) &&
		match(cur, OPERATOR_ASSIGNMENT) &&
		Expression(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Dimension_Wildcards(Node* Parent){

	ExpressionNode* cur = new ExpressionNode("Dimension_Wildcards");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, LEFT_BRACKET) &&
		Dimension_Args(cur) &&
		match(cur, RIGHT_BRACKET)) ||
		(cur->deleteChildren());
}

bool Parser::Dimension_Args(Node* Parent){

	ExpressionNode* cur = new ExpressionNode("Dimension_Args");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, COMMA) && Dimension_Args(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (true)))) ||
		(cur->deleteChildren());
}



bool Parser::Variable_Declaration(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Variable_Declaration");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (Variable_Declaration_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Variable_Declaration_2(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Variable_Declaration_3(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Variable_Declaration_4(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Variable_Declaration_5(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Variable_Declaration_6(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::Variable_Declaration_1(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Variable_Declaration_1");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_STATIC) &&
		match(cur, KEYWORD_CONST) &&
		match(cur, KEYWORD_VAR) &&
		match(cur, IDENTIFIER) &&
		Type_Descriptor(cur) &&
		match(cur, SEMICOLON)) ||
		(cur->deleteChildren());
}

bool Parser::Variable_Declaration_2(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Variable_Declaration_2");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_CONST) &&
		match(cur, KEYWORD_VAR) &&
		match(cur, IDENTIFIER) &&
		Type_Descriptor(cur) &&
		match(cur, SEMICOLON)) ||
		(cur->deleteChildren());
}

bool Parser::Variable_Declaration_3(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Variable_Declaration_3");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_VAR) &&
		match(cur, IDENTIFIER) &&
		Type_Descriptor(cur) &&
		match(cur, SEMICOLON)) ||
		(cur->deleteChildren());
}

bool Parser::Variable_Declaration_4(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Variable_Declaration_4");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_STATIC) &&
		match(cur, KEYWORD_CONST) &&
		match(cur, KEYWORD_VAR) &&
		match(cur, IDENTIFIER) &&
		match(cur, OPERATOR_COMPAREEQUAL) &&
		Expression(cur) &&
		match(cur, SEMICOLON)) ||
		(cur->deleteChildren());
}

bool Parser::Variable_Declaration_5(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Variable_Declaration_5");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_CONST) &&
		match(cur, KEYWORD_VAR) &&
		match(cur, IDENTIFIER) &&
		match(cur, OPERATOR_ASSIGNMENT) &&
		Expression(cur) &&
		match(cur, SEMICOLON)) ||
		(cur->deleteChildren());
}

bool Parser::Variable_Declaration_6(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Variable_Declaration_6");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_VAR) &&
		match(cur, IDENTIFIER) &&
		match(cur, OPERATOR_ASSIGNMENT) &&
		Expression(cur) &&
		match(cur, SEMICOLON)) ||
		(cur->deleteChildren());

}

bool Parser::Block_Statement(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Block_Statement");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, LEFT_CURLY_BRACE) &&
		Statements(cur) &&
		match(cur, RIGHT_CURLY_BRACE)) ||
		(cur->deleteChildren());
}

bool Parser::For_Statement(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("For_Statement");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_FOR) &&
		match(cur, LEFT_PAREN) &&
		Expression(cur) &&
		match(cur, SEMICOLON) &&
		Expression(cur) &&
		match(cur, SEMICOLON) &&
		Expression(cur) &&
		match(cur, RIGHT_PAREN) &&
		Block_Statement(cur)) ||
		(cur->deleteChildren());
}

bool Parser::While_Statement(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("While_Statement");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_WHILE) &&
		match(cur, LEFT_PAREN) &&
		Expression(cur) &&
		match(cur, RIGHT_PAREN) &&
		Block_Statement(cur)) ||
		(cur->deleteChildren());
}

bool Parser::If_Statement(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("If_Statement");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (If_Statement_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (If_Statement_2(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::If_Statement_1(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("If_Statement_1");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_IF) &&
		match(cur, LEFT_PAREN) &&
		Expression(cur) &&
		Block_Statement(cur) &&
		match(cur, LEFT_PAREN) &&
		match(cur, KEYWORD_ELSE) &&
		Block_Statement(cur) &&
		match(cur, RIGHT_PAREN)) ||
		(cur->deleteChildren());
}

bool Parser::If_Statement_2(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("If_Statement_2");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_IF) &&
		match(cur, LEFT_PAREN) &&
		Expression(cur) &&
		Block_Statement(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Print_Statement(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Print_Statement");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_PRINT) &&
		Expression(cur) &&
		match(cur, SEMICOLON)) ||
		(cur->deleteChildren());
}

bool Parser::Return_Statement(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Return_Statement");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (Return_Statement_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Return_Statement_2(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::Return_Statement_1(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Return_Statement_1");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_RETURN) &&
		Expression(cur) &&
		match(cur, SEMICOLON)) ||
		(cur->deleteChildren());
}

bool Parser::Return_Statement_2(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Return_Statement_2");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_RETURN) &&
		match(cur, SEMICOLON)) ||
		(cur->deleteChildren());
}

bool Parser::Exit_Statement(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Exit_Statement");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (Exit_Statement_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Exit_Statement_2(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::Exit_Statement_1(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Exit_Statement_1");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_EXIT) &&
		Expression(cur) &&
		match(cur, SEMICOLON)) ||
		(cur->deleteChildren());
}

bool Parser::Exit_Statement_2(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Exit_Statement_2");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, KEYWORD_EXIT) &&
		match(cur, SEMICOLON)) ||
		(cur->deleteChildren());
}

bool Parser::Expression_Statement(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expression_Statement");
	Parent->children.push_back(cur);

	// printTree();


	return (Expression(cur) &&
		match(cur, SEMICOLON)) ||
		(cur->deleteChildren());
}

bool Parser::Expressions(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expressions");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (Expression(cur) && Expressions_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Expression(cur) && Expressions_2(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::Expressions_1(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expressions_1");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, COMMA) &&
		Expression(cur) &&
		Expressions(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Expressions_2(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expressions_2");
	Parent->children.push_back(cur);

	// printTree();


	return (true) ||
		(cur->deleteChildren());
}

bool Parser::Expression(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expression");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (Expression_10(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Expression_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Expression_2(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Expression_3(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Expression_4(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Expression_5(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Expression_6(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Expression_7(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Expression_8(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Expression_9(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::Expression_1(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expression_1");
	Parent->children.push_back(cur);

	// printTree();


	return (Type_Cast(cur) &&
		Additional_Expression(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Expression_2(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expression_2");
	Parent->children.push_back(cur);

	// printTree();


	return (Function_Call(cur) &&
		Additional_Expression(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Expression_3(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expression_3");
	Parent->children.push_back(cur);

	// printTree();


	return (Variable(cur) &&
		Additional_Expression(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Expression_4(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expression_4");
	Parent->children.push_back(cur);

	// printTree();


	return (Number(cur) &&
		Additional_Expression(cur)) ||
		(cur->deleteChildren());
}

//DOUBLE CHECK TO SEE IF CORRECT
bool Parser::Expression_5(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expression_5");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, STRING_LITERAL) &&
		Additional_Expression(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Expression_6(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expression_6");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, LEFT_PAREN) &&
		Expression(cur) &&
		match(cur, RIGHT_PAREN) &&
		Additional_Expression(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Expression_7(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expression_7");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, OPERATOR_EXCLAMATION_POINT) &&
		Expression(cur) &&
		Additional_Expression(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Expression_8(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expression_8");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, OPERATOR_TILDE) &&
		Expression(cur) &&
		Additional_Expression(cur)) ||
		(cur->deleteChildren());
}

/*May need to split Operator Minus and Unary Minus*/

bool Parser::Expression_9(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expression_9");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, OPERATOR_MINUS) &&
		Expression(cur) &&
		Additional_Expression(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Expression_10(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Expression_10");
	Parent->children.push_back(cur);

	// printTree();


	return (Variable(cur) &&
		match(cur, OPERATOR_ASSIGNMENT) &&
		Expression(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (Additional_Expression_ADD(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_2(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_3(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_4(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_5(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_6(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_7(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_8(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_9(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_10(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_11(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_12(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_13(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_14(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_15(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_16(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Expression_END(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_ADD(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_ADD");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_PLUS) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_2(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_2");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_MINUS) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_3(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_3");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_ASTERISK) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_4(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_4");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_DIVISION) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_5(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_5");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_BITWISE_AND) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_6(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_6");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_BITWISE_OR) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_7(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_7");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_LEFT_SHIFT) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_8(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_8");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_RIGHT_SHIFT) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_9(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_9");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_COMPAREEQUAL) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_10(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_10");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_NOT_EQUAL) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_11(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_11");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_LESS_THAN) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_12(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_12");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_LESS_OR_EQUAL) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_13(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_13");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_GREATER_THAN) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_14(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_14");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_GREATER_OR_EQUAL) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_15(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_15");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_LOGICAL_AND) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_16(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_16");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, OPERATOR_LOGICAL_OR) && Expression(cur) && Additional_Expression(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (false)))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Expression_END(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Expression_END");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return true;
}


bool Parser::Type_Cast(Node* Parent) {

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Type_Cast");
	Parent->children.push_back(cur);

	// printTree();


	return (Basic_Type(cur) &&
		match(cur, LEFT_PAREN) &&
		Expression(cur) &&
		match(cur, RIGHT_PAREN)) ||
		(cur->deleteChildren());
}

bool Parser::Function_Call(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Function_Call");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (Function_Call_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Function_Call_2(cur))))) ||
		(cur->deleteChildren());
}
bool Parser::Function_Call_1(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Function_Call_1");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, IDENTIFIER) &&
		match(cur, LEFT_PAREN) &&
		Expressions(cur) &&
		match(cur, RIGHT_PAREN)) ||
		(cur->deleteChildren());
}

bool Parser::Function_Call_2(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Function_Call_2");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, IDENTIFIER) &&
		match(cur, LEFT_PAREN) &&
		match(cur, RIGHT_PAREN)) ||
		(cur->deleteChildren());

}

bool Parser::Variable(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Variable");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (Variable_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Variable_2(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::Variable_1(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Variable_1");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, IDENTIFIER)) ||
		(cur->deleteChildren());
}

bool Parser::Variable_2(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Variable_2");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, IDENTIFIER) &&
		Subscript(cur) &&
		Additional_Variables(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Variables(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Variables");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (Additional_Variables_1(cur)))) ||
		(nextToken = save, (cur->deleteChildren() || (Additional_Variables_2(cur))))) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Variables_1(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Variables_1");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, OPERATOR_DOT) &&
		Variable(cur) &&
		Additional_Variables(cur)) ||
		(cur->deleteChildren());
}

bool Parser::Additional_Variables_2(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Additional_Variables_2");
	Parent->children.push_back(cur);

	// printTree();


	return (true) ||
		(cur->deleteChildren());
}

bool Parser::Subscript(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Subscript");
	Parent->children.push_back(cur);

	// printTree();


	return (match(cur, LEFT_BRACKET) &&
		Expressions(cur) &&
		match(cur, RIGHT_BRACKET)) ||
		(cur->deleteChildren());
}

bool Parser::Number(Node* Parent){

	// printTree();

	ExpressionNode* cur = new ExpressionNode("Number");
	Parent->children.push_back(cur);

	// printTree();


	std::vector<Token>::iterator save = nextToken;
	return ((nextToken = save, (cur->deleteChildren() || (match(cur, CHARACTER_LITERAL)))) ||
		(nextToken = save, (cur->deleteChildren() || (match(cur, INTEGER)))) ||
		(nextToken = save, (cur->deleteChildren() || (match(cur, FLOAT_LEADING_DIGIT)))) ||
		(nextToken = save, (cur->deleteChildren() || (match(cur, FLOAT_LEADING_DECIMAL)))) ||
		(nextToken = save, (cur->deleteChildren() || (match(cur, FLOAT_NO_DECIMAL))))) ||
		(cur->deleteChildren());
}

