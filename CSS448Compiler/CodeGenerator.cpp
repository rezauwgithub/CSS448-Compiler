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
string CodeGenerator::declareInt32(string initialValue){
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
		out << "\t\t" << "int_literal " << declaredInt32s[i] << endl;
	}
}

void CodeGenerator::generateAssembly(ostream& out) {

	generateAssemblyFromSubtree(parseTreeRoot, out);

	generateDeclaredInt32s(out);
}

void CodeGenerator::generateAssemblyFromSubtree(Node* curSubtree, ostream& out) {
	
	Node* curNode = curSubtree;
	
	// postorder traversal

	// generate assembly for children of the current node (if there are any)
	for (int i = 0; i < curNode->children.size(); i++) {
		generateAssemblyFromSubtree(curNode->children[i], out);
	}

	// generate assembly for the current node

	// if the node is a token
	if (curNode->expressionType == "") {

		enum TokenClass curTokenClass = curNode->token.getTokenClass();

		// if the node is an int32

		string label;

		switch (curTokenClass) {
		case INTEGER:
			label = declareInt32(curNode->token.getTokenText());
			out << "\t\t" << "load_label " << label << endl;
			out << "\t\t" << "load_mem_int" << endl;
			break;

		case STRING_LITERAL:
			break;
		}
	}
	else { // the node is not a token.
		if (false) {
			//TODO
		}

	}
}

void CodeGenerator::printTree() {
	parseTreeRoot->printSubtree(0);
}