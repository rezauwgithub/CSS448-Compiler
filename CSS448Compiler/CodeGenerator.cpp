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

int CodeGenerator::numDeclaredInt32s = 0;


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


std::string CodeGenerator::getAllAssemblyStrIntLiterals()
{
    stringstream ss;
    
    for (int i = 0; i < strIntLiterals.size(); i++)
    {
        ss << strIntLiterals.at(i) << "\n"; 
    }
    
    
    return ss.str();
}

std::string CodeGenerator::getAllAssemblyInt32IntLiterals() 
{
    stringstream ss;
    
    for (int i = 0; i < int32IntLiterals.size(); i++)
    {
        ss << strIntLiterals.at(i) << "\n"; 
    }
    
    
    return ss.str();
}


std::string CodeGenerator::getAllAssemblyFloatInterLiterals()
{
    stringstream ss;
    
    for (int i = 0; i < floatIntLiterals.size(); i++)
    {
        ss << floatIntLiterals.at(i) << "\n"; 
    }
    
    
    return ss.str();   
}


void CodeGenerator::preOutputAssemblyStr(std::string str, std::ostream& oStream)
{
    stringstream ss;
    
    ss << "\tload_label " << 
    ss << generateAssemblyStrIntLiteral(str);// returns label
          
    ss << "\n\tload_label printString";
    ss << "\n\tcall\n\n";

        
        
        
    ss << "\tload_label done\n";
    ss << "\tbranch\n";
        
    ss << "\n\n";
        
        
    ss << generateAssemblyStrLoop();        // returns loop
        
    ss << "\n\n";
        
        
    ss << generateAssemblyStrDone();        // returns done
        
        
    ss << "\n\n";
    
    oStream << ss.str();
}


void CodeGenerator::outputAssemblyStrIntLiterals(std::string str, std::ostream& oStream)
{
    stringstream ss;
        
    ss << generateAssemblyStrIntLiteral(str);// returns label
    ss << getAllAssemblyStrIntLiterals();         // returns allStrings
        
        
    ss << "\n\n";

    
    oStream << ss.str();
}



void CodeGenerator::outputAssemblyInt32IntLiterals(std::string str, std::ostream& oStream)
{
    stringstream ss;
        
    ss << "\t" << "load_label " << generateAssemblyInt32IntLiteral(str) << endl;
    ss << "\t" << "load_mem_int" << "\n";                

    int currentLabelNumber = 0;
    for (int i = 0; i < int32IntLiterals.size(); i++) {
        currentLabelNumber = i + 1;
        ss << "int32_" + to_string(currentLabelNumber) << ":" << "\n";
        ss << "\t" << "int_literal " << int32IntLiterals[i] << "\n";
    }
        
    oStream << ss;
}


void CodeGenerator::outputAssemblyFloatIntLiterals(std::string str, std::ostream& oStream)
{
    oStream << generateAssemblyFloatIntLiteral(str);
}


void CodeGenerator::outputAssembly(std::string str, std::ostream& oStream) {

    generateAssemblyFromSubtree(parseTreeRoot, oStream);

    outputAssemblyStrIntLiterals(str, oStream);
    outputAssemblyInt32IntLiterals(str, oStream);
    outputAssemblyFloatIntLiterals(str, oStream);       
}


std::string CodeGenerator::generateAssemblyStrLoop()
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


std::string CodeGenerator::generateAssemblyStrDone() 
{
    stringstream ss;
    
    ss << "done:\n";
    ss << "\tload0\n";
    ss << "\texit\n";
    
    return ss.str();
}




std::string CodeGenerator::generateAssemblyStrIntLiteral(std::string str)
{   
    int currentVectorIndex = strIntLiterals.size() + 1;
    
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
    
    
    strIntLiterals.push_back(ss.str());
    
    return label;
}


// the default initialValue is zero.
std::string CodeGenerator::generateAssemblyInt32IntLiteral(std::string int32 = "0"){
	numDeclaredInt32s++;

	int32IntLiterals.push_back(int32);

	return "int32_" + to_string(numDeclaredInt32s);

}


std::string CodeGenerator::generateAssemblyFloatIntLiteral(std::string fl = "0.0")
{
    return "Got here!";
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

void CodeGenerator::generateAssemblyFromSubtree(Node* curSubtree, std::ostream& oStream) {
	
	Node* curNode = curSubtree;
	
	// postorder traversal

	// generate assembly for children of the current node (if there are any)
	for (int i = 0; i < curNode->children.size(); i++) {
		generateAssemblyFromSubtree(curNode->children[i], oStream);
	}


	// generate assembly for the current node

	// if the node is a token
	if (curNode->expressionType == "") {

		enum TokenClass curTokenClass = curNode->token.getTokenClass();

		// if the node is an int32

		string label;

		switch (curTokenClass) {
		case INTEGER:
			outputAssemblyInt32IntLiterals(curNode->token.getTokenText(), oStream);
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