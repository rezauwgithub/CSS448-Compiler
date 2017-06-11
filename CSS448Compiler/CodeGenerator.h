/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CodeGenerator.h
 * Author: rezan
 *
 * Created on June 8, 2017, 11:41 PM
 */
#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "Node.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class CodeGenerator 
{
public:
    CodeGenerator();
    CodeGenerator(const CodeGenerator& orig);
    virtual ~CodeGenerator();
        
        

	void importParseTree(Node* treeRoot);
        
        
	//string declareData();
        
        std::string getAllAssemblyStrIntLiterals();
        std::string getAllAssemblyInt32IntLiterals();
        std::string getAllAssemblyFloatInterLiterals();
        
        void preOutputAssemblyStr(std::string str, std::ostream& oStream);
        
        void outputAssemblyStrIntLiterals(std::string str, std::ostream& oStream);
	void outputAssemblyInt32IntLiterals(std::string str, std::ostream& oStream);
        void outputAssemblyFloatIntLiterals(std::string str, std::ostream& oStream);
 
        
        
	// generate the assembly code from our AST.
	void outputAssembly(std::string str, std::ostream& oStream = cout);

        
        std::string generateAssemblyStrLoop();
        std::string generateAssemblyStrDone();
        
        std::string generateAssemblyStrIntLiteral(std::string str);
        // This makes sure that an int will get declared in the assembly which is generated.
	// You may provide an initial value for the int, but the default value is 0.
	// The method returns the label where the int is stored.
        std::string generateAssemblyInt32IntLiteral(std::string int32);
        std::string generateAssemblyFloatIntLiteral(std::string fl);
        
        

        

	void printTree();
	void getNextIdentifier(Node* curr, string*& id);
	void generateAssemblyFromSubtree(Node* curSubtree, std::ostream& oStream);

private:
    
        vector<std::string> strIntLiterals;
        vector<std::string> int32IntLiterals;       // each int32's value is stored as a string.
        vector<std::string> floatIntLiterals;       // each float's value is stored as a string.
    
        
	Node* parseTreeRoot;

	int numDeclaredInt32s = 0;
	
        
        
};

#endif /* CODEGENERATOR_H */

