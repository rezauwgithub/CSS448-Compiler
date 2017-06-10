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
	numDeclaredInt32s = 0;

}

CodeGenerator::CodeGenerator(const CodeGenerator& orig) {
}

CodeGenerator::~CodeGenerator() {
}

void CodeGenerator::importParseTree(Node* treeRoot) {
	parseTreeRoot = treeRoot;
}

// the default initialValue is zero.
string CodeGenerator::declareInt32(int initialValue){
	numDeclaredInt32s++;

	declaredInt32s.push_back(initialValue);

	return "int32_" + to_string(numDeclaredInt32s);

}

// output defaults to cout.
void CodeGenerator::generateDeclaredInt32s(ostream& out) {
	int currentLabelNumber = 0;
	for (int i = 0; i < declaredInt32s.size(); i++) {
		currentLabelNumber = i + 1;
		out << "int32_" + to_string(currentLabelNumber) << ":" << endl;
		out << "\t\t" << "int_literal " << to_string(declaredInt32s[i]) << endl;
	}
}