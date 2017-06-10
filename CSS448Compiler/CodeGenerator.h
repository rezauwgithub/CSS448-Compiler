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

class CodeGenerator {
public:
    CodeGenerator();
    CodeGenerator(const CodeGenerator& orig);
    virtual ~CodeGenerator();

	void importParseTree(Node* treeRoot);

private:
	Node* parseTreeRoot;
};

#endif /* CODEGENERATOR_H */

