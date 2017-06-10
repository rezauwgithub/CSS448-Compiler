/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CodeGenerator.cpp
 * Author: rezan
 * 
 * Created on June 8, 2017, 11:41 PM
 */

#include "CodeGenerator.h"

CodeGenerator::CodeGenerator() {
}

CodeGenerator::CodeGenerator(const CodeGenerator& orig) {
}

CodeGenerator::~CodeGenerator() {
}

void CodeGenerator::importParseTree(Node* treeRoot) {
	parseTreeRoot = treeRoot;
}