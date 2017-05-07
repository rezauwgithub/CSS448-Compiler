/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.cpp
 * Author: Daniel
 * 
 * Created on May 2, 2017, 11:46 PM
 */

#include <stack>

#include "Parser.h"

Parser::Parser(Lexer lexer)
{
    *next = lexer.tokens.front();
}


bool Parser::term(TokenClass tClass)
{    
    if((*next++).getTokenClass() == tClass)
    {        
        enqueueReversePolishQueue(*next);
        return true;
    }
    else
    {
        return false;
    }
}

void Parser::enqueueReversePolishQueue(Token tok)
{
        switch(tok.getTokenClass()){
            
        //ALL NON OPERATORS
        case(COMMA):
        case(SEMICOLON):
        case(WHITESPACE):
        case(KEYWORD_BYTE):
        case(KEYWORD_CONST):
        case(KEYWORD_ELSE):
        case(KEYWORD_END):
        case(KEYWORD_EXIT):
        case(KEYWORD_FLOAT64):
        case(KEYWORD_FOR):
        case(KEYWORD_FUNCTION):
        case(KEYWORD_IF):
        case(KEYWORD_INT32):
        case(KEYWORD_PRINT):
        case(KEYWORD_RECORD):
        case(KEYWORD_REF):
        case(KEYWORD_RETURN):
        case(KEYWORD_STATIC):
        case(KEYWORD_TYPE):
        case(KEYWORD_VAR):
        case(KEYWORD_WHILE):
        case(IDENTIFIER):
        case(CHARACTER_LITERAL):
        case(INTEGER):
        case(FLOAT_LEADING_DIGIT):
        case(FLOAT_LEADING_DECIMAL):
        case(FLOAT_NO_DECIMAL):
            
            reversePolishQueue.push(tok);
            break;
            
        //ALL OPERATORS    
        case (LEFT_PAREN):
        case(RIGHT_PAREN):
        case(LEFT_BRACKET):
        case(RIGHT_BRACKET):
        case(LEFT_CURLY_BRACE):
        case(RIGHT_CURLY_BRACE):
        case(OPERATOR_MINUS):
        case(OPERATOR_EXCLAMATION_POINT):
        case(OPERATOR_TILDE):
        case(OPERATOR_ASTERISK):
        case(OPERATOR_DIVISION):
        case(OPERATOR_PLUS):
        case(OPERATOR_DOT):
        case(OPERATOR_ARROW):
        case(OPERATOR_LEFT_SHIFT):
        case(OPERATOR_RIGHT_SHIFT):
        case(OPERATOR_LESS_THAN):
        case(OPERATOR_LESS_OR_EQUAL):
        case(OPERATOR_GREATER_THAN):
        case(OPERATOR_GREATER_OR_EQUAL):
        case(OPERATOR_EQUAL):
        case(OPERATOR_NOT_EQUAL):
        case(OPERATOR_AMPERSAND):
        case(OPERATOR_BITWISE_AND):
        case(OPERATOR_BITWISE_OR):
        case(OPERATOR_LOGICAL_AND):
        case(OPERATOR_LOGICAL_OR):
        case(OPERATOR_ASSIGNMENT):
            
            if (operatorsStack.empty() || 
                tok.getPrecedence() > operatorsStack.top().getPrecedence() ||
                tok.getTokenClass() == LEFT_CURLY_BRACE ||
                tok.getTokenClass() == LEFT_BRACKET ||
                tok.getTokenClass() == LEFT_PAREN)
            {                
                operatorsStack.push(tok);
                operatorsStack.pop();
            }
            
            else if(operatorsStack.top().getTokenClass() == RIGHT_CURLY_BRACE ||    //If the operator at top of the stack is a right enclosure...
                    operatorsStack.top().getTokenClass() == RIGHT_BRACKET ||        
                    operatorsStack.top().getTokenClass() == RIGHT_PAREN)
            {
                while(tok.getTokenClass() != LEFT_CURLY_BRACE ||    //While the operator at top of the stack is not a left enclosure, 
                        tok.getTokenClass() != LEFT_BRACKET ||      //push to reverse polish queue. Then pop off from operator stack.
                        tok.getTokenClass() != LEFT_PAREN)
                {
                    popOperatorStackToReversePolishQueue();                          
                }
                operatorsStack.pop();   //While loop will exit if top of stack is left enclosure. Pop from the stack.
            }

            else if(operatorsStack.top().getPrecedence() >= tok.getPrecedence()) 
            {
                while(operatorsStack.top().getPrecedence() >= tok.getPrecedence())
                {
                    popOperatorStackToReversePolishQueue();
                }                
            }
            
            while(!operatorsStack.empty())                           //While the operator stack contains operators
            {                                                       //pop them over to Reverse Polish Queue
                popOperatorStackToReversePolishQueue();
            }
     
            break;   
    }
}

void Parser::popOperatorStackToReversePolishQueue()
{
    reversePolishQueue.push(operatorsStack.top());
    operatorsStack.pop();
}

//void Parser::OrderOperatorsAndNonOperators()
//{
//    if(reversePolishQueue.front()==)
//    while(reversePolishQueue.front())
//}

bool Parser::Statement()
{
    Token* save = next;
    return (next = save, Declaration_Statement()) ||
            (next = save, Block_Statement()) ||
            (next = save, For_Statement()) ||
            (next = save, While_Statement()) ||
            (next = save, If_Statement()) ||
            (next = save, Print_Statement()) ||
            (next = save, Return_Statement()) ||
            (next = save, Exit_Statement()) ||
            (next = save, Expression_Statement());
}

bool Parser::Declaration_Statement(){
    Token* save = next;
    return (next = save, Type_Declaration()) ||
            (next = save, Function_Declaration()) ||
            (next = save, Variable_Declaration());
}

bool Parser::Type_Declaration(){
    return term(KEYWORD_TYPE) && term(IDENTIFIER) && Type_Descriptor();
}

bool Parser::Type_Descriptor(){
    Token* save = next;
    return (next = save, Type_Descriptor_1()) ||
            (next = save, Type_Descriptor_2());
}

bool Parser::Type_Descriptor_1(){
    return Non_Array_Type_Descriptor();
}

bool Parser::Type_Descriptor_2(){
    return Non_Array_Type_Descriptor() && Dimension();
}

bool Parser::Non_Array_Type_Descriptor()
{
    Token* save = next;
    return (next = save, Record_Descriptor()) ||
            (next = save, term(IDENTIFIER)) ||
            (next = save, Basic_Type());
}


bool Parser::Record_Descriptor()
{
    
    
    return term(KEYWORD_RECORD) && Field_Declarations() && term(KEYWORD_END);
}


bool Parser::Field_Declarations()
{
    return Field_Declaration() && Multiple_Field_Declarations();
}

bool Parser::Multiple_Field_Declarations()
{
    Token* save = next;
    return (next = save, Multiple_Field_Declarations_1()) ||
            (next = save, Multiple_Field_Declarations_2());
            
}

bool Parser::Multiple_Field_Declarations_1()
{
    return term(COMMA) && Field_Declaration() && Multiple_Field_Declarations();
}

bool Parser::Multiple_Field_Declarations_2()
{
    return true;
}

bool Parser::Field_Declaration()
{
    return term(IDENTIFIER) && Type_Descriptor();
}

bool Parser::Basic_Type()
{
    Token* save = next;
    return (next = save, term(KEYWORD_BYTE)) ||
            (next = save, term(KEYWORD_INT32)) ||
            (next = save, term(KEYWORD_FLOAT64));
}

bool Parser::Dimension()
{
    return term(LEFT_BRACKET) && Expression() && term(RIGHT_BRACKET);
}

bool Parser::Function_Declaration()
{
    Token* save = next;
    return (next = save, Function_Declaration_1()) ||
            (next = save, Function_Declaration_2()) ||
            (next = save, Function_Declaration_3());
}

bool Parser::Function_Declaration_1()
{
    return term(KEYWORD_FUNCTION) && term(IDENTIFIER) && Block_Statement();
}

bool Parser::Function_Declaration_2()
{
    return term(KEYWORD_FUNCTION) && term(IDENTIFIER) && term(RIGHT_PAREN) 
            && Parameters() && term(LEFT_PAREN) && Block_Statement();
}

bool Parser::Function_Declaration_3()
{
    return term(KEYWORD_FUNCTION) && term(IDENTIFIER) && term(RIGHT_PAREN) 
            && Parameters() && term(LEFT_PAREN) && Type_Descriptor() && Block_Statement();
}


bool Parser::Parameters()
{
    return Parameter() && Additional_Parameters();
}

bool Parser::Additional_Parameters()
{
    Token* save = next;
    return (next = save, Additional_Parameters_1()) ||
            (next = save, Additional_Parameters_2());
}

bool Parser::Additional_Parameters_1()
{
    return term(COMMA) && Parameter() && Additional_Parameters();
}

bool Parser::Additional_Parameters_2()
{
    return true;
}

bool Parser::Parameter()
{
    Token* save = next;
    return (next = save, Parameter_1()) ||
            (next = save, Parameter_2()) ||
            (next = save, Parameter_3()) ||
            (next = save, Parameter_4()) ||
            (next = save, Parameter_5());
}

bool Parser::Parameter_1()
{
    term(KEYWORD_REF) && term(KEYWORD_CONST) && term(IDENTIFIER) 
            && Non_Array_Type_Descriptor() && Dimension_Wildcards();
}

bool Parser::Parameter_2()
{
    term(KEYWORD_CONST) && term(IDENTIFIER) && Non_Array_Type_Descriptor() 
            && Dimension_Wildcards();
}

bool Parser::Parameter_3()
{
    term(IDENTIFIER) && Non_Array_Type_Descriptor() && Dimension_Wildcards();
}

bool Parser::Parameter_4()
{
    term(IDENTIFIER) && Non_Array_Type_Descriptor();
}

bool Parser::Parameter_5()
{
    term(KEYWORD_REF) && term(KEYWORD_CONST) && term(IDENTIFIER) && term(OPERATOR_ASSIGNMENT) 
            && Expression();
}

bool Parser::Dimension_Wildcards(){
    return term(LEFT_BRACKET) && Dimension_Args() && term(RIGHT_BRACKET);
}

bool Parser::Dimension_Args(){
    Token* save=next;
    return (next=save, term(COMMA) && Dimension_Args()) ||
            (next=save, true);
}



bool Parser::Variable_Declaration()
{
    Token* save = next;
    return (next = save, Variable_Declaration_1()) ||
            (next = save, Variable_Declaration_2()) ||
            (next = save, Variable_Declaration_3()) ||
            (next = save, Variable_Declaration_4()) ||
            (next = save, Variable_Declaration_5()) ||
            (next = save, Variable_Declaration_6());
}

bool Parser::Variable_Declaration_1()
{
    term(KEYWORD_STATIC) && term(KEYWORD_CONST) && term(KEYWORD_VAR) && term(IDENTIFIER) && Type_Descriptor();
}

bool Parser::Variable_Declaration_2()
{
    term(KEYWORD_CONST) && term(KEYWORD_VAR) && term(IDENTIFIER) && Type_Descriptor();
}

bool Parser::Variable_Declaration_3()
{
    term(KEYWORD_VAR) && term(IDENTIFIER) && Type_Descriptor();
}

bool Parser::Variable_Declaration_4()
{
    term(KEYWORD_STATIC) && term(KEYWORD_CONST) && term(KEYWORD_VAR) && term(IDENTIFIER) && term(OPERATOR_EQUAL) && Expression();
}

bool Parser::Variable_Declaration_5()
{
    term(KEYWORD_CONST) && term(KEYWORD_VAR) && term(IDENTIFIER) && term(OPERATOR_EQUAL) && Expression();
}

bool Parser::Variable_Declaration_6()
{
    term(KEYWORD_VAR) && term(IDENTIFIER) && term(OPERATOR_EQUAL) && Expression();

}

bool Parser::Block_Statement()
{
    return term(LEFT_CURLY_BRACE) && Additional_Statements() && term(RIGHT_CURLY_BRACE);
}

bool Parser::Additional_Statements()
{
    Token* save = next;
    return (next = save, Additional_Statements_1()) ||
            (next = save, Additional_Statements_2());
}

bool Parser::Additional_Statements_1()
{
    return Statement() && Additional_Statements();
}

bool Parser::Additional_Statements_2()
{
    return true;
}

bool Parser::For_Statement()
{
    return term(KEYWORD_FOR) && term(LEFT_PAREN) && Expression() && term(SEMICOLON)
            && Expression() && term(SEMICOLON) && Expression() && term(SEMICOLON)
            && term(RIGHT_PAREN) && Block_Statement();
}

bool Parser::While_Statement()
{
    return term(KEYWORD_WHILE) && term(LEFT_PAREN) && Expression() && term(RIGHT_PAREN) && Block_Statement();
}

bool Parser::If_Statement()
{
    Token* save = next;
    return (next = save, If_Statement_1()) ||
            (next = save, If_Statement_2());
}

bool Parser::If_Statement_1()
{
    return term(KEYWORD_IF) && term(LEFT_PAREN) && Expression() && Block_Statement() 
            && term(LEFT_PAREN) && term(KEYWORD_ELSE) && Block_Statement()
            && term(RIGHT_PAREN);
}

bool Parser::If_Statement_2()
{
    return term(KEYWORD_IF) && term(LEFT_PAREN) && Expression() && Block_Statement();
        
}

bool Parser::Print_Statement()
{
    return term(KEYWORD_PRINT) && Expression();
}

bool Parser::Return_Statement()
{
    Token* save = next;
    return (next = save, Return_Statement_1()) ||
            (next = save, Return_Statement_2());
}

bool Parser::Return_Statement_1()
{
    return term(KEYWORD_RETURN) && Expression();
}

bool Parser::Return_Statement_2()
{
    return term(KEYWORD_RETURN);
}

bool Parser::Exit_Statement()
{
    Token* save = next;
    return (next = save, Exit_Statement_1()) ||
            (next = save, Exit_Statement_2());
}

bool Parser::Exit_Statement_1()
{
    return term(KEYWORD_EXIT) && Expression();
}

bool Parser::Exit_Statement_2()
{
    return term(KEYWORD_EXIT);
}

bool Parser::Expression_Statement()
{
    return Expression();
}

bool Parser::Expressions()
{
    Token* save = next;
    return (next = save, Expressions_1()) ||
            (next = save, Expressions_2());
}

bool Parser::Expressions_1()
{
    return term(COMMA) && Expression() && Expressions();
}

bool Parser::Expressions_2()
{
    return true;
}

bool Parser::Expression()
{
    Token* save = next;
    return (next = save, Expression_1()) ||
            (next = save, Expression_2()) ||
            (next = save, Expression_3()) ||
            (next = save, Expression_4()) ||
            (next = save, Expression_5()) ||
            (next = save, Expression_6()) ||
            (next = save, Expression_7()) ||
            (next = save, Expression_8()) ||
            (next = save, Expression_9());
}

bool Parser::Expression_1()
{
    return Type_Cast() && Additional_Expression();
}

bool Parser::Expression_2()
{
    return Function_Call() && Additional_Expression();
}

bool Parser::Expression_3(){
    return Variable() && Additional_Expression();
}

bool Parser::Expression_4(){
    return Number() && Additional_Expression();
}

//DOUBLE CHECK TO SEE IF CORRECT
bool Parser::Expression_5(){
    return term(STRING_LITERAL) && Additional_Expression();
}

bool Parser::Expression_6(){
    return term(LEFT_PAREN) && Expression() && term(RIGHT_PAREN) && Additional_Expression();
}

bool Parser::Expression_7(){
    return term(OPERATOR_EXCLAMATION_POINT) && Expression() && Additional_Expression();
}

bool Parser::Expression_8(){
    return term(OPERATOR_TILDE) && Expression() && Additional_Expression();
}

/*May need to split Operator Minus and Unary Minus*/

bool Parser::Expression_9(){
    return term(OPERATOR_MINUS) && Expression() && Additional_Expression();
}

bool Parser::Additional_Expression(){
    Token* save=next;
    return (next=save, Additional_Expression_1()) ||
            (next=save, Additional_Expression_2()) ||
            (next=save, Additional_Expression_3()) ||
            (next=save, Additional_Expression_4()) ||
            (next=save, Additional_Expression_5()) ||
            (next=save, Additional_Expression_6()) ||
            (next=save, Additional_Expression_7()) ||
            (next=save, Additional_Expression_8()) ||
            (next=save, Additional_Expression_9()) ||
            (next=save, Additional_Expression_10()) ||
            (next=save, Additional_Expression_11()) ||
            (next=save, Additional_Expression_12()) ||
            (next=save, Additional_Expression_13()) ||
            (next=save, Additional_Expression_14()) ||
            (next=save, Additional_Expression_15()) ||
            (next=save, Additional_Expression_16());
}

bool Parser::Additional_Expression_1(){
    Token* save=next;
    return (next=save, term(OPERATOR_PLUS) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_2(){
    Token* save=next;
    return(next=save, term(OPERATOR_MINUS) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_3(){
    Token* save=next;
    return(next=save, term(OPERATOR_ASTERISK) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_4(){
    Token* save=next;
    return(next=save, term(OPERATOR_DIVISION) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_5(){
    Token* save=next;
    return(next=save, term(OPERATOR_BITWISE_AND) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_6(){
    Token* save=next;
    return(next=save, term(OPERATOR_BITWISE_OR) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_7(){
    Token* save=next;
    return(next=save, term(OPERATOR_LEFT_SHIFT) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_8(){
    Token* save=next;
    return(next=save, term(OPERATOR_RIGHT_SHIFT) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_9(){
    Token* save=next;
    return(next=save, term(OPERATOR_EQUAL) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_10(){
    Token* save=next;
    return(next=save, term(OPERATOR_NOT_EQUAL) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_11(){
    Token* save=next;
    return(next=save, term(OPERATOR_LESS_THAN) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_12(){
    Token* save=next;
    return(next=save, term(OPERATOR_LESS_OR_EQUAL) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_13(){
    Token* save=next;
    return(next=save, term(OPERATOR_GREATER_THAN) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_14(){
    Token* save=next;
    return(next=save, term(OPERATOR_GREATER_OR_EQUAL) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_15(){
    Token* save=next;
    return(next=save, term(OPERATOR_LOGICAL_AND) && Expression() && Additional_Expression()) ||
            (next=save, true);
}

bool Parser::Additional_Expression_16(){
    Token* save=next;
    return(next=save, term(OPERATOR_LOGICAL_OR) && Expression() && Additional_Expression()) ||
            (next=save, true);
}


bool Parser::Type_Cast() 
{
    return Basic_Type() && term(LEFT_PAREN) && Expression() && term(RIGHT_PAREN);
}

bool Parser::Function_Call()
{
    Token* save = next;
    return (next = save, Function_Call_1()) ||
            (next = save, Function_Call_2());
}
bool Parser::Function_Call_1()
{
    return term(IDENTIFIER) && term(LEFT_PAREN) && Expressions() && term(RIGHT_PAREN);
}

bool Parser::Function_Call_2()
{
    return term(IDENTIFIER) && term(LEFT_PAREN) && term(RIGHT_PAREN);
    
}

bool Parser::Variable()
{
    Token* save = next;
    return (next = save, Variable_1()) ||
            (next = save, Variable_2());
}

bool Parser::Variable_1()
{
    return term(IDENTIFIER);            
}

bool Parser::Variable_2()
{
    return term(IDENTIFIER) && Subscript() && Additional_Variables();
}
    
bool Parser::Additional_Variables()
{
    Token* save = next;
    return  (next = save, Additional_Variables_1()) ||
            (next = save, Additional_Variables_2());
}

bool Parser::Additional_Variables_1()
{
    return term(OPERATOR_DOT) && Variable() && Additional_Variables();
}

bool Parser::Additional_Variables_2()
{
    return true;
}

bool Parser::Subscript()
{
    return term(LEFT_BRACKET) && Expressions() && term(RIGHT_BRACKET);
}

bool Parser::Number()
{
    Token* save = next;
    return (next = save, term(CHARACTER_LITERAL)) ||
            (next = save, term(INTEGER)) ||
            (next = save, term(FLOAT_LEADING_DIGIT)) ||
            (next = save, term(FLOAT_LEADING_DECIMAL)) ||
            (next = save, term(FLOAT_NO_DECIMAL));
}
