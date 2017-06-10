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

class CodeGenerator {
public:
    CodeGenerator();
    CodeGenerator(const CodeGenerator& orig);
    virtual ~CodeGenerator();

	void importParseTree(Node* treeRoot);

	// generate the assembly code from our AST.
	void generateAssembly(ostream& out = cout);

	// This makes sure that an int will get declared in the assembly which is generated.
	// You may provide an initial value for the int, but the default value is 0.
	// The method returns the label where the int is stored.
	string declareInt32(string initialValue = "0");

	//string declareData();

	void generateDeclaredInt32s(ostream& out = cout);

	void printTree();

	void generateAssemblyFromSubtree(Node* curSubtree, ostream& out);

private:
	Node* parseTreeRoot;

	int numDeclaredInt32s = 0;
	vector<string> declaredInt32s; // each int32's value is stored as a string.
};

#endif /* CODEGENERATOR_H */

