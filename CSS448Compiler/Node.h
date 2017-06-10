/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: Daniel
 *
 * Created on May 15, 2017, 11:49 AM
 */

#ifndef NODE_H
#define NODE_H

#include <string>
#include "Token.h"

static int x = 0;

class Node{
public:
    std::vector<Node*> children;
	std::string expressionType;
	Token token;

    //int depth;
	
	//Node() {

	//};

	bool deleteChildren() {
		//cout << "---- " << this->expressionType << " deleted something:" << endl;

		//if (this->expressionType != "" && this->children.size() != 0) {
		//	x = x + 1;
		//	this->printSubtree(x);
		//	x = 0;
		//}



		//cout << "----DONE----" << endl;


		//if (this->expressionType == "Program") {
		//	cout << "Oh shit!" << endl;
		//	
		//}
		
		int i = children.size() - 1;
		while (i >= 0) {
			if (children[i] != NULL) {
				delete children[i];
				children[i] = NULL;
			}
			children.pop_back();
			i--;
		}

		return false;
	};
	
	void printSubtree(int currentIndent) {
		//if (children.empty()) {
		if (this->expressionType == "") {
			for (int j = 0; j < currentIndent; j++) {
				cout << "\t";
			}
			//cout << "[" << token.getLineNumber() << "," << token.getColumnNumber() << "] "
			//	<< token.getTokenClassChar() << endl;

			cout << this->token;
			cout << endl;
		}
		else {
			for (int j = 0; j < currentIndent; j++) {
				cout << "\t";
			}
			cout << this->expressionType << endl;

			for (int i = 0; i < children.size(); i++) {
				children[i]->printSubtree(currentIndent + 1);
			}
		}
	};

};




class ExpressionNode : public Node{
public:
    ExpressionNode(std::string expType) {expressionType = expType;}
    //std::string expressionType;
};


class TokenNode : public Node{
public:
    TokenNode(Token tok) {token = tok;}
    //Token token;
};

#endif /* NODE_H */
