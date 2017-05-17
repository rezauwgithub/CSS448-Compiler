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

Parser::Parser(queue<Token> tokenQueue) {
    nextToken = &tokenQueue.front();
}

bool Parser::match(TokenClass nextGrammarTokenClass) {
    
        //Check if look-ahead token's class == Class of next token of a grammar
        if((*nextToken++).getTokenClass() == nextGrammarTokenClass) {   
            return true;
        }
        else
            return false;
}

bool Parser::Program(){
    return Statements();
}

bool Parser::Statements()
{
    if(nextToken != NULL) {
        return Statements_1();
    }
    else {
        return Statements_2();
    }
}

bool Parser::Statements_1(){
    return Statement() && 
            Statements();
}

bool Parser::Statements_2(){
    return true;
}

bool Parser::Statement(){
    switch(nextToken->getTokenClass()){
        case(KEYWORD_TYPE):
        case(KEYWORD_FUNCTION):
        case(KEYWORD_STATIC):
        case(KEYWORD_CONST):
        case(KEYWORD_VAR):
            return Declaration_Statement();

        case(LEFT_CURLY_BRACE):
            return Block_Statement();

        case(KEYWORD_FOR):
            return For_Statement();

        case(KEYWORD_WHILE):
            return While_Statement();

        case(KEYWORD_IF):
            return If_Statement();

        case(KEYWORD_PRINT):
            return Print_Statement();

        case(KEYWORD_RETURN):
            return Return_Statement();

        case(KEYWORD_EXIT):
            return Exit_Statement();

        //Check logic for this case
        default:
            return Expression_Statement();
    }
}

bool Parser::Declaration_Statement(){
    switch(nextToken->getTokenClass()){
        case(KEYWORD_TYPE):
            return Type_Declaration();
            
        case(KEYWORD_FUNCTION):
            return Function_Declaration();
            
        case(KEYWORD_STATIC):
        case(KEYWORD_CONST):
        case(KEYWORD_VAR):
            return Variable_Declaration();
    }
}

bool Parser::Type_Declaration(){
    return match(KEYWORD_TYPE) && 
            match(IDENTIFIER) && 
            Type_Descriptor() && 
            match(SEMICOLON);
}

bool Parser::Type_Descriptor(){
    Token* save = nextToken;
    
    return(nextToken = save, Type_Descriptor_1()) ||
          (nextToken = save, Type_Descriptor_2());
}

bool Parser::Type_Descriptor_1(){
    return Non_Array_Type_Descriptor() && 
            Dimension();
}

bool Parser::Type_Descriptor_2(){
    return Non_Array_Type_Descriptor();
}

bool Parser::Non_Array_Type_Descriptor(){
    switch(nextToken->getTokenClass()){
        case(KEYWORD_RECORD):
            return Record_Descriptor();
            
        case(IDENTIFIER):
            return match(IDENTIFIER);
            
        case(KEYWORD_BYTE):
        case(KEYWORD_INT32):
        case(KEYWORD_FLOAT64):
            return Basic_Type();
    }
}

bool Parser::Record_Descriptor(){    
    return match(KEYWORD_RECORD) && 
            Field_Declarations() && 
            match(KEYWORD_END);
}


bool Parser::Field_Declarations(){
    Token* save = nextToken;
    
    return(nextToken = save, Field_Declarations_1()) ||
          (nextToken = save, Field_Declarations_2()) ||
          (nextToken = save, Field_Declarations_3());
}

bool Parser::Field_Declarations_1(){
    return Field_Declaration() && Field_Declarations();
}

bool Parser::Field_Declarations_2(){
    return match(COMMA) && Field_Declarations();
}
bool Parser::Field_Declarations_3(){
    return true;
}

bool Parser::Field_Declaration(){
    return match(IDENTIFIER) && 
            Type_Descriptor();
}

bool Parser::Basic_Type(){
    switch(nextToken->getTokenClass()){
        case(KEYWORD_BYTE):
            return match(KEYWORD_BYTE);
        case(KEYWORD_INT32):
            return match(KEYWORD_INT32);
        case(KEYWORD_FLOAT64):
            return match(KEYWORD_FLOAT64);
    }
}

bool Parser::Dimension(){
    return match(LEFT_BRACKET) && 
            Expression() && 
            match(RIGHT_BRACKET);
}

bool Parser::Function_Declaration(){
    Token* save = nextToken;
    return
            (nextToken = save, Function_Declaration_1()) ||
            (nextToken = save, Function_Declaration_2()) ||
            (nextToken = save, Function_Declaration_3());
}

bool Parser::Function_Declaration_1(){
    return match(KEYWORD_FUNCTION) && 
            match(IDENTIFIER) && 
            match(LEFT_PAREN) && 
            match(RIGHT_PAREN) && 
            Block_Statement();
}

bool Parser::Function_Declaration_2(){
    return match(KEYWORD_FUNCTION) && 
            match(IDENTIFIER) && 
            match(LEFT_PAREN)&& 
            Parameters() && 
            match(RIGHT_PAREN) && 
            Block_Statement();
}

bool Parser::Function_Declaration_3(){
    return match(KEYWORD_FUNCTION) && 
            match(IDENTIFIER) && 
            match(LEFT_PAREN) && 
            Parameters() && 
            match(RIGHT_PAREN) && 
            Type_Descriptor() && 
            Block_Statement();
}


bool Parser::Parameters(){
    Token* save = nextToken;
    return (nextToken = save, Parameters_1()) ||
           (nextToken = save, Parameters_2()) ||
           (nextToken = save, Parameters_3());
}

bool Parser::Parameters_1(){
    return Parameter() && Parameters();
}

bool Parser::Parameters_2(){
    return match(COMMA) && Parameters_1();
}

bool Parser::Parameters_3(){
    return true;
}

bool Parser::Parameter(){
    Token* save = nextToken;
    return (nextToken = save, Parameter_1()) ||
            (nextToken = save, Parameter_2()) ||
            (nextToken = save, Parameter_3()) ||
            (nextToken = save, Parameter_4()) ||
            (nextToken = save, Parameter_5());
}

bool Parser::Parameter_1(){
    return match(KEYWORD_REF) && 
            match(KEYWORD_CONST) && 
            match(IDENTIFIER) && 
            Non_Array_Type_Descriptor() && 
            Dimension_Wildcards();
}

bool Parser::Parameter_2(){
    return match(KEYWORD_CONST) && 
            match(IDENTIFIER) && 
            Non_Array_Type_Descriptor() && 
            Dimension_Wildcards();
}

bool Parser::Parameter_3(){
    return match(IDENTIFIER) && 
            Non_Array_Type_Descriptor() && 
            Dimension_Wildcards();
}

bool Parser::Parameter_4(){
    return match(IDENTIFIER) && 
            Non_Array_Type_Descriptor();
}

bool Parser::Parameter_5(){
    return match(KEYWORD_REF) && 
            match(KEYWORD_CONST) && 
            match(IDENTIFIER) && 
            match(OPERATOR_ASSIGNMENT) && 
            Expression();
}

bool Parser::Dimension_Wildcards(){
    return match(LEFT_BRACKET) && 
            Dimension_Args() && 
            match(RIGHT_BRACKET);
}

bool Parser::Dimension_Args(){
    Token* save=nextToken;
    return (nextToken=save, match(COMMA) && Dimension_Args()) ||
            (nextToken=save, true);
}



bool Parser::Variable_Declaration(){
    Token* save = nextToken;
    return (nextToken = save, Variable_Declaration_1()) ||
            (nextToken = save, Variable_Declaration_2()) ||
            (nextToken = save, Variable_Declaration_3()) ||
            (nextToken = save, Variable_Declaration_4()) ||
            (nextToken = save, Variable_Declaration_5()) ||
            (nextToken = save, Variable_Declaration_6());
}

bool Parser::Variable_Declaration_1(){
    return match(KEYWORD_STATIC) && 
            match(KEYWORD_CONST) && 
            match(KEYWORD_VAR) && 
            match(IDENTIFIER) && 
            Type_Descriptor() && 
            match(SEMICOLON);
}

bool Parser::Variable_Declaration_2(){
    return match(KEYWORD_CONST) && 
            match(KEYWORD_VAR) && 
            match(IDENTIFIER) && 
            Type_Descriptor() && 
            match(SEMICOLON);
}

bool Parser::Variable_Declaration_3(){
    return match(KEYWORD_VAR) && 
            match(IDENTIFIER) && 
            Type_Descriptor() && 
            match(SEMICOLON);
}

bool Parser::Variable_Declaration_4(){
    return match(KEYWORD_STATIC) && 
            match(KEYWORD_CONST) && 
            match(KEYWORD_VAR) && 
            match(IDENTIFIER) && 
            match(OPERATOR_EQUAL) && 
            Expression() && 
            match(SEMICOLON);
}

bool Parser::Variable_Declaration_5(){
    return match(KEYWORD_CONST) && 
            match(KEYWORD_VAR) && 
            match(IDENTIFIER) && 
            match(OPERATOR_EQUAL) && 
            Expression() && 
            match(SEMICOLON);
}

bool Parser::Variable_Declaration_6(){
    return match(KEYWORD_VAR) && 
            match(IDENTIFIER) && 
            match(OPERATOR_EQUAL) && 
            Expression() && 
            match(SEMICOLON);

}

bool Parser::Block_Statement(){
    return match(LEFT_CURLY_BRACE) && 
            Statements() && 
            match(RIGHT_CURLY_BRACE);
}

bool Parser::For_Statement(){
    return match(KEYWORD_FOR) && 
            match(LEFT_PAREN) && 
            Expression() && 
            match(SEMICOLON) && 
            Expression() && 
            match(SEMICOLON) && 
            Expression() && 
            match(SEMICOLON) && 
            match(RIGHT_PAREN) && 
            Block_Statement();
}

bool Parser::While_Statement(){
    return match(KEYWORD_WHILE) && 
            match(LEFT_PAREN) && 
            Expression() && 
            match(RIGHT_PAREN) && 
            Block_Statement();
}

bool Parser::If_Statement(){
    Token* save = nextToken;
    return (nextToken = save, If_Statement_1()) ||
            (nextToken = save, If_Statement_2());
}

bool Parser::If_Statement_1(){
    return match(KEYWORD_IF) && 
            match(LEFT_PAREN) && 
            Expression() && 
            Block_Statement() && 
            match(LEFT_PAREN) && 
            match(KEYWORD_ELSE) && 
            Block_Statement() && 
            match(RIGHT_PAREN);
}

bool Parser::If_Statement_2(){
    return match(KEYWORD_IF) && 
            match(LEFT_PAREN) && 
            Expression() && 
            Block_Statement();        
}

bool Parser::Print_Statement(){
    return match(KEYWORD_PRINT) && 
            Expression() && 
            match(SEMICOLON);
}

bool Parser::Return_Statement(){
    Token* save = nextToken;
    return (nextToken = save, Return_Statement_1()) ||
            (nextToken = save, Return_Statement_2());
}

bool Parser::Return_Statement_1(){
    return match(KEYWORD_RETURN) && 
            Expression() && 
            match(SEMICOLON);
}

bool Parser::Return_Statement_2(){
    return match(KEYWORD_RETURN) && 
            match(SEMICOLON);
}

bool Parser::Exit_Statement(){
    Token* save = nextToken;
    return (nextToken = save, Exit_Statement_1()) ||
            (nextToken = save, Exit_Statement_2());
}

bool Parser::Exit_Statement_1(){
    return match(KEYWORD_EXIT) && 
            Expression() && 
            match(SEMICOLON);
}

bool Parser::Exit_Statement_2(){
    return match(KEYWORD_EXIT) && 
            match(SEMICOLON);
}

bool Parser::Expression_Statement(){
    return Expression() && 
            match(SEMICOLON);
}

bool Parser::Expressions(){
    Token* save = nextToken;
    return (nextToken = save, Expressions_1()) ||
            (nextToken = save, Expressions_2());
}

bool Parser::Expressions_1(){
    return match(COMMA) && 
            Expression() && 
            Expressions();
}

bool Parser::Expressions_2(){
    return true;
}

bool Parser::Expression(){
    Token* save = nextToken;
    return (nextToken = save, Expression_1()) ||
            (nextToken = save, Expression_2()) ||
            (nextToken = save, Expression_3()) ||
            (nextToken = save, Expression_4()) ||
            (nextToken = save, Expression_5()) ||
            (nextToken = save, Expression_6()) ||
            (nextToken = save, Expression_7()) ||
            (nextToken = save, Expression_8()) ||
            (nextToken = save, Expression_9());
}

bool Parser::Expression_1(){
    return Type_Cast() && 
            Additional_Expression();
}

bool Parser::Expression_2(){
    return Function_Call() && 
            Additional_Expression();
}

bool Parser::Expression_3(){
    return Variable() && 
            Additional_Expression();
}

bool Parser::Expression_4(){
    return Number() && 
            Additional_Expression();
}

//DOUBLE CHECK TO SEE IF CORRECT
bool Parser::Expression_5(){
    return match(STRING_LITERAL) && 
            Additional_Expression();
}

bool Parser::Expression_6(){
    return match(LEFT_PAREN) && 
            Expression() && 
            match(RIGHT_PAREN) && 
            Additional_Expression();
}

bool Parser::Expression_7(){
    return match(OPERATOR_EXCLAMATION_POINT) && 
            Expression() && 
            Additional_Expression();
}

bool Parser::Expression_8(){
    return match(OPERATOR_TILDE) && 
            Expression() && 
            Additional_Expression();
}

/*May need to split Operator Minus and Unary Minus*/

bool Parser::Expression_9(){
    return match(OPERATOR_MINUS) && 
            Expression() && 
            Additional_Expression();
}

bool Parser::Additional_Expression(){
    Token* save=nextToken;
    return (nextToken=save, Additional_Expression_1()) ||
            (nextToken=save, Additional_Expression_2()) ||
            (nextToken=save, Additional_Expression_3()) ||
            (nextToken=save, Additional_Expression_4()) ||
            (nextToken=save, Additional_Expression_5()) ||
            (nextToken=save, Additional_Expression_6()) ||
            (nextToken=save, Additional_Expression_7()) ||
            (nextToken=save, Additional_Expression_8()) ||
            (nextToken=save, Additional_Expression_9()) ||
            (nextToken=save, Additional_Expression_10()) ||
            (nextToken=save, Additional_Expression_11()) ||
            (nextToken=save, Additional_Expression_12()) ||
            (nextToken=save, Additional_Expression_13()) ||
            (nextToken=save, Additional_Expression_14()) ||
            (nextToken=save, Additional_Expression_15()) ||
            (nextToken=save, Additional_Expression_16());
}

bool Parser::Additional_Expression_1(){
    Token* save=nextToken;
    return (nextToken=save, match(OPERATOR_PLUS) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_2(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_MINUS) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_3(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_ASTERISK) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_4(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_DIVISION) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_5(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_BITWISE_AND) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_6(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_BITWISE_OR) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_7(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_LEFT_SHIFT) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_8(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_RIGHT_SHIFT) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_9(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_EQUAL) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_10(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_NOT_EQUAL) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_11(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_LESS_THAN) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_12(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_LESS_OR_EQUAL) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_13(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_GREATER_THAN) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_14(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_GREATER_OR_EQUAL) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_15(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_LOGICAL_AND) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}

bool Parser::Additional_Expression_16(){
    Token* save=nextToken;
    return(nextToken=save, match(OPERATOR_LOGICAL_OR) && Expression() && Additional_Expression()) ||
            (nextToken=save, true);
}


bool Parser::Type_Cast() {
    return Basic_Type() && 
            match(LEFT_PAREN) && 
            Expression() && 
            match(RIGHT_PAREN);
}

bool Parser::Function_Call(){
    Token* save = nextToken;
    return (nextToken = save, Function_Call_1()) ||
            (nextToken = save, Function_Call_2());
}
bool Parser::Function_Call_1(){
    return match(IDENTIFIER) && 
            match(LEFT_PAREN) && 
            Expressions() && 
            match(RIGHT_PAREN);
}

bool Parser::Function_Call_2(){
    return match(IDENTIFIER) && 
            match(LEFT_PAREN) && 
            match(RIGHT_PAREN);
    
}

bool Parser::Variable(){
    Token* save = nextToken;
    return (nextToken = save, Variable_1()) ||
            (nextToken = save, Variable_2());
}

bool Parser::Variable_1(){
    return match(IDENTIFIER);            
}

bool Parser::Variable_2(){
    return match(IDENTIFIER) && 
            Subscript() && 
            Additional_Variables();
}
    
bool Parser::Additional_Variables(){
    Token* save = nextToken;
    return  (nextToken = save, Additional_Variables_1()) ||
            (nextToken = save, Additional_Variables_2());
}

bool Parser::Additional_Variables_1(){
    return match(OPERATOR_DOT) && 
            Variable() && 
            Additional_Variables();
}

bool Parser::Additional_Variables_2(){
    return true;
}

bool Parser::Subscript(){
    return match(LEFT_BRACKET) && 
            Expressions() && 
            match(RIGHT_BRACKET);
}

bool Parser::Number(){
    Token* save = nextToken;
    return (nextToken = save, match(CHARACTER_LITERAL)) ||
            (nextToken = save, match(INTEGER)) ||
            (nextToken = save, match(FLOAT_LEADING_DIGIT)) ||
            (nextToken = save, match(FLOAT_LEADING_DECIMAL)) ||
            (nextToken = save, match(FLOAT_NO_DECIMAL));
}

