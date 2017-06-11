/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SymbolTable.cpp
 * Author: Daniel
 * 
 * Created on June 8, 2017, 9:29 PM
 */

#include "SymbolTable.h"

using namespace std;

bool SymbolTable::findSymbol(std::string var){
    if(symbolTable.find(var) == symbolTable.end()) {
       return true;
    }
    else {
        return false;
    }
}

void SymbolTable::addSymbol(std::string var, Node* tokenNode){
    symbolTable.insert(pair<string, Node*>(var, tokenNode));
}
