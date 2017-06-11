/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SemanticAnalyzer.h
 * Author: Daniel
 *
 * Created on June 8, 2017, 9:08 PM
 */

#ifndef SEMANTICANALYZER_H
#define SEMANTICANALYZER_H

#include "Node.h"
#include "SymbolTable.h"
#include <string>

class SemanticAnalyzer{
public:
    SemanticAnalyzer(Node*);
    
private:
    Node* AST;
    std::vector<SymbolTable> symbolTableVector;
    
    void verifyVariables(Node*);
    void getNextIdentifier(Node*, Node*&);
    void typeCheck(Node*);
    bool scopeCheck(Node*);
    void enterScope();
    void exitScope();    
    void constructSymbolTable();
    void addNewVariable(std::string, Node*);
};

#endif /* SEMANTICANALYZER_H */
