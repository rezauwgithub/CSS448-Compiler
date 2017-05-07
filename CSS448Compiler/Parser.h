/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: Daniel
 *
 * Created on May 5, 2017, 4:14 PM
 */

#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "Lexer.h"

class Parser
{
    private:
        //std::queue<Token> tokenString;
       
        Token* next;
        
        std::queue<Token> reversePolishQueue;
        std::stack<Token> operatorsStack;
        
        std::queue<Token> operatorQueue;
        std::stack<Token> nonOperatorStack;
        
        void enqueueReversePolishQueue(Token);
        void popOperatorStackToReversePolishQueue();
        void createAST();
        void orderOperatorsAndNonOperators();
        
        
        

    public:
        
        Parser(Lexer);

        bool term(TokenClass);
        bool Statement();
        bool Declaration_Statement();
        bool Type_Declaration();       
        bool Type_Descriptor();
            bool Type_Descriptor_1();
            bool Type_Descriptor_2();            
        bool Non_Array_Type_Descriptor();
        bool Record_Descriptor();
        bool Field_Declarations();
        bool Multiple_Field_Declarations();
            bool Multiple_Field_Declarations_1();
            bool Multiple_Field_Declarations_2();            
        bool Field_Declaration();
        bool Basic_Type();
        bool Dimension();
        bool Function_Declaration();
            bool Function_Declaration_1();
            bool Function_Declaration_2();
            bool Function_Declaration_3();            
        bool Parameters();
        bool Additional_Parameters();
            bool Additional_Parameters_1();
            bool Additional_Parameters_2();            
        bool Parameter();
            bool Parameter_1();
            bool Parameter_2();
            bool Parameter_3();
            bool Parameter_4();
            bool Parameter_5();




        //++++++++++++++++++++++++
        //++++++++++++++++++++++++
        //Dimension Wildcard
        //++++++++++++++++++++++++
        //++++++++++++++++++++++++
            bool Dimension_Wildcards();
            bool Dimension_Args();




        bool Variable_Declaration();
            bool Variable_Declaration_1();
            bool Variable_Declaration_2();
            bool Variable_Declaration_3();
            bool Variable_Declaration_4();
            bool Variable_Declaration_5();
            bool Variable_Declaration_6();
        bool Block_Statement();
        bool Additional_Statements();
            bool Additional_Statements_1();
            bool Additional_Statements_2();
        bool For_Statement();
        bool While_Statement();
        bool If_Statement();
            bool If_Statement_1();
            bool If_Statement_2();
        bool Print_Statement();
        bool Return_Statement();
            bool Return_Statement_1();
            bool Return_Statement_2();
        bool Exit_Statement();
            bool Exit_Statement_1();
            bool Exit_Statement_2();
        bool Expression_Statement();
        bool Expressions();
            bool Expressions_1();
            bool Expressions_2();

        //+++++++++++++++++++++++++++
        //+++++++++++++++++++++++++++
        // EXPRESSIONS GO HERE
        //+++++++++++++++++++++++++++
        //+++++++++++++++++++++++++++ 
        bool Expression();
            bool Expression_1();
            bool Expression_2();
            bool Expression_3();
            bool Expression_4();
            bool Expression_5();
            bool Expression_6();
            bool Expression_7();
            bool Expression_8();
            bool Expression_9();
        bool Additional_Expression();
            bool Additional_Expression_1();
            bool Additional_Expression_2();
            bool Additional_Expression_3();
            bool Additional_Expression_4();
            bool Additional_Expression_5();
            bool Additional_Expression_6();
            bool Additional_Expression_7();
            bool Additional_Expression_8();
            bool Additional_Expression_9();
            bool Additional_Expression_10();
            bool Additional_Expression_11();
            bool Additional_Expression_12();
            bool Additional_Expression_13();
            bool Additional_Expression_14();
            bool Additional_Expression_15();
            bool Additional_Expression_16();
        bool Type_Cast();
        bool Function_Call();
            bool Function_Call_1();
            bool Function_Call_2();
        bool Variable();
        bool Variable_1();
        bool Variable_2();
        bool Additional_Variables();
            bool Additional_Variables_1();
            bool Additional_Variables_2();
        bool Subscript();
        bool Number();

        
};


#endif /* PARSER_H */