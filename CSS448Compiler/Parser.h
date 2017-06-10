/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: Daniel
 *
 * Created on May 16, 2017, 2:58 PM
 */

#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Token.h"
#include "Node.h"

class Parser{
public:
    Parser();

	std::vector<Token> tokens;
	void parseTokens(std::vector<Token>);
	void printTree();
	Node* copyTree();

    
private:
	std::vector<Token>::iterator nextToken;
	Node*   parseTreeRoot;

	void readInTokens(std::vector<Token>);

    /**********************/
    /**      GRAMMAR     **/
    /**********************/
        bool match(TokenClass); // TODO: remove
		bool match(Node*, TokenClass);
        
		bool Program(Node*);

		bool Statements(Node*);
		bool Statements_1(Node*);
		bool Statements_END(Node*);

		bool Statement(Node*);

		bool Declaration_Statement(Node*);

		bool Type_Declaration(Node*);

		bool Type_Descriptor(Node*);
		bool Type_Descriptor_1(Node*);
		bool Type_Descriptor_2(Node*);

		bool Non_Array_Type_Descriptor(Node*);
		bool Record_Descriptor(Node*);

		bool Multiple_Field_Declarations(Node*);
		bool Multiple_Field_Declarations_1(Node*);
		bool Multiple_Field_Declarations_2(Node*);

		bool Field_Declarations(Node*);
		bool Field_Declarations_1(Node*);
		bool Field_Declarations_2(Node*);
		bool Field_Declarations_3(Node*);

		bool Field_Declaration(Node*);

		bool Basic_Type(Node*);

		bool Dimension(Node*);

		bool Function_Declaration(Node*);
		bool Function_Declaration_1(Node*);
		bool Function_Declaration_2(Node*);
		bool Function_Declaration_3(Node*);

		bool Parameters(Node*);
		bool Parameters_1(Node*);
		bool Parameters_2(Node*);
		bool Parameters_3(Node*);

		bool Parameter(Node*);
		bool Parameter_1(Node*);
		bool Parameter_2(Node*);
		bool Parameter_3(Node*);
		bool Parameter_4(Node*);
		bool Parameter_5(Node*);

		bool Dimension_Wildcards(Node*);

		bool Dimension_Args(Node*);

		bool Variable_Declaration(Node*);
		bool Variable_Declaration_1(Node*);
		bool Variable_Declaration_2(Node*);
		bool Variable_Declaration_3(Node*);
		bool Variable_Declaration_4(Node*);
		bool Variable_Declaration_5(Node*);
		bool Variable_Declaration_6(Node*);

		bool Block_Statement(Node*);

		bool For_Statement(Node*);

		bool While_Statement(Node*);

		bool If_Statement(Node*);
		bool If_Statement_1(Node*);
		bool If_Statement_2(Node*);

		bool Print_Statement(Node*);

		bool Return_Statement(Node*);
		bool Return_Statement_1(Node*);
		bool Return_Statement_2(Node*);

		bool Exit_Statement(Node*);
		bool Exit_Statement_1(Node*);
		bool Exit_Statement_2(Node*);

		bool Expression_Statement(Node*);

		bool Expressions(Node*);
		bool Expressions_1(Node*);
		bool Expressions_2(Node*);

		bool Expression(Node*);
		bool Expression_1(Node*);
		bool Expression_2(Node*);
		bool Expression_3(Node*);
		bool Expression_4(Node*);
		bool Expression_5(Node*);
		bool Expression_6(Node*);
		bool Expression_7(Node*);
		bool Expression_8(Node*);
		bool Expression_9(Node*);
		bool Expression_10(Node*);

		bool Additional_Expression(Node*);
		bool Additional_Expression_1(Node*);
		bool Additional_Expression_2(Node*);
		bool Additional_Expression_3(Node*);
		bool Additional_Expression_4(Node*);
		bool Additional_Expression_5(Node*);
		bool Additional_Expression_6(Node*);
		bool Additional_Expression_7(Node*);
		bool Additional_Expression_8(Node*);
		bool Additional_Expression_9(Node*);
		bool Additional_Expression_10(Node*);
		bool Additional_Expression_11(Node*);
		bool Additional_Expression_12(Node*);
		bool Additional_Expression_13(Node*);
		bool Additional_Expression_14(Node*);
		bool Additional_Expression_15(Node*);
		bool Additional_Expression_16(Node*);
		bool Additional_Expression_END(Node*);


		bool Type_Cast(Node*);

		bool Function_Call(Node*);
		bool Function_Call_1(Node*);
		bool Function_Call_2(Node*);

		bool Variable(Node*);
		bool Variable_1(Node*);
		bool Variable_2(Node*);

		bool Additional_Variables(Node*);
		bool Additional_Variables_1(Node*);
		bool Additional_Variables_2(Node*);

		bool Subscript(Node*);

		bool Number(Node*);
};

#endif /* PARSER_H */
