/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SymbolTable.h
 * Author: Daniel
 *
 * Created on June 8, 2017, 9:29 PM
 */

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <string>
#include <map>
#include "Node.h"

class SymbolTable{
public:
    bool findSymbol(std::string);      //Find current X
    void addSymbol(std::string, Node*);
private:
    std::map<std::string, Node*> symbolTable;   
};

#endif /* SYMBOLTABLE_H */
