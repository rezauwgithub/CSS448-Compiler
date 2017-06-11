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




std::string CodeGenerator::generateAssemblyCodeForStringIntL(std::string str)
{   
    int currentVectorIndex = declaredStrings.size() + 1;
    
    stringstream ss;
    ss << "string_" << currentVectorIndex;
    std::string label = ss.str();
    
    ss.str("");
    
    ss << label << ":\n";
            
    
    for (int i = 0; i < str.length(); i++)
    {
        ss << "\tint_literal " << (int)str[i] << "\n";
    }
            
    
    // # null
    ss << "\tint_literal 0\n";
    
    
    declaredStrings.push_back(ss.str());
    
    return label;
}


std::string CodeGenerator::getAssemblyCodeForAllStringsIntL()
{
    stringstream ss;
    
    for (int i = 0; i < declaredStrings.size(); i++)
    {
        ss << declaredStrings.at(i) << "\n"; 
    }
    
    
    return ss.str();
}


std::string CodeGenerator::generateAssemblyCodeForStringLoop()
{
    stringstream ss;
    
    // # copy address and load character pointed
    ss << "printString:\n";
    ss << "printString_loop:\n";
    ss << "\tdup\n";
    ss << "\tload_mem_int\n";
    
    ss << "\n";
    
    // # done if character is 0 (string terminator)
    ss << "\tdup\n";
    ss << "\tload_label printString_done\n";
    ss << "\tbranch_zero\n";
    
    ss << "\n";
        
    // # otherwise, print character
    ss << "\tprint_byte\n";
            
    
    ss << "\n";
    
    
    //  # increment the string pointer to get next character
    ss << "\tload1\n";
    ss << "\tadd\n";
    
    
    ss << "\n";
    
    // # and repeat
    ss << "\tload_label printString_loop\n";
    ss << "\tbranch\n";
    
    ss << "printString_done:\n";
    
    ss << "\treturn\n";
    
    
    return ss.str();
}


std::string CodeGenerator::generateAssemblyCodeForStringDone() 
{
    stringstream ss;
    
    ss << "done:\n";
    ss << "\tload0\n";
    ss << "\texit\n";
    
    return ss.str();
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
		out << "\t" << "int_literal " << declaredInt32s[i] << endl;
	}
}

void CodeGenerator::generateAssembly(ostream& out) {

	generateAssemblyFromSubtree(parseTreeRoot, out);

	generateDeclaredInt32s(out);
}

void CodeGenerator::getNextIdentifier(Node* curr, string*& id) {
	
	if (curr->token.getTokenClass() == IDENTIFIER) {
		id = new string(curr->token.getTokenText());
		return;
	}
	
	if (curr->children.empty()) {
		return;
	}
	else {
		for (int i = 0; i < curr->children.size(); i++) {
			getNextIdentifier(curr->children[i], id);
		}
	}
	return;
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
			out << "\t" << "load_label " << label << endl;
			out << "\t" << "load_mem_int" << endl;
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