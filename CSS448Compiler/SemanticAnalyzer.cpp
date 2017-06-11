/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SemanticAnalyzer.cpp
 * Author: Daniel
 * 
 * Created on June 8, 2017, 9:08 PM
 */

#include "SemanticAnalyzer.h"
#include <iostream>
#include <valarray>

using namespace std;

SemanticAnalyzer::SemanticAnalyzer(Node* astRoot){
    /* Traverse AST
     * If you arrive at PARAMETER / BLOCK_STATEMENT node, enterScope()
     * 
     * You enter a new scope whenever you enter a new block statement
     * Inside a new scope, push any newly declared symbol into the symbol table
     * Check to see if any symbols being used is in the symbol table
     * 
     * If you arrive at the end of a block statement, exitScope()
     * 
     */
    verifyVariables(astRoot);
    typeCheck(astRoot);        
}

void SemanticAnalyzer::verifyVariables(Node* curr){
    if(curr->token.getTokenText() == "Variable_Declaration"){
        Node* n;
        getNextIdentifier(curr, n);
        symbolTableVector.front().addSymbol(n->token.getTokenText(), n);
    }
    if(curr->token.getTokenText() == "Block_Statement"){
        constructSymbolTable();
        for(int i = 0; i < curr->children.size(); i++){
            verifyVariables(curr->children[i]);
        }
        exitScope();
    }
    if(curr->children.empty()){
        return;
    }
    else
    {
        for(int i = 0; i < curr->children.size(); i++){
            verifyVariables(curr->children[i]);
        }
    }
}

void SemanticAnalyzer::typeCheck(Node* astRoot){
    
}

void SemanticAnalyzer::getNextIdentifier(Node* curr, Node*& n){
    if (curr->token.getTokenClass() == IDENTIFIER) {
        n = curr;
        return;
    }
   
    if (curr->children.empty()) {
        return;
    }
    else {
        for (int i = 0; i < curr->children.size(); i++) {
            getNextIdentifier(curr->children[i], n);
        }
    }
    return;
}

//Check if variable exists in current scope's symbol table
bool SemanticAnalyzer::scopeCheck(Node* identifier) {    
    bool found;
    string variable = identifier->token.getTokenText();
    for(int i = 0; i < symbolTableVector.size(); i++){
        found = symbolTableVector[i].findSymbol(variable);
    }
    return found;    
    
}

//Creates new scope symbol table and adds to symbol table "stack"
void SemanticAnalyzer::constructSymbolTable(){
    SymbolTable* newScopeSymbolTable = new SymbolTable;
    symbolTableVector.insert(symbolTableVector.begin(),*newScopeSymbolTable);
}

//Adds newly declared variable into current symbol table
void SemanticAnalyzer::addNewVariable(string var, Node* token){
    symbolTableVector.front().addSymbol(var, token);
}

//Pop current symbol table upon exiting scope;
void SemanticAnalyzer::exitScope(){
    //Pop current symbol table upon exiting scope
    symbolTableVector.erase(symbolTableVector.begin());
}

