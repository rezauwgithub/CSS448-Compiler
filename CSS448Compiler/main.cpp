/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Daniel
 *
 * Created on April 11, 2017, 8:28 AM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "Lexer.h"
#include "Parser.h"
#include "Node.h"
#include "CodeGenerator.h"


using namespace std;

/*
 * The program takes the path to the source file as a command line argument.
 */
int main(int argc, char** argv) {
	
	const char* myFilePath;
	if (argc > 1) {
		myFilePath = argv[1];
	}
	else {
		myFilePath = "source.txt";
	}
	cout << "Input file path: " << myFilePath << endl;

    Lexer lex(myFilePath);

        

	Parser parser;
	parser.parseTokens(lex.getTokens());

	CodeGenerator gen;
	gen.importParseTree(parser.copyTree());

	cout << "---- Tree ---" << endl;
	gen.printTree();
	cout << "---- Done ---" << endl;

        
	cout << "---- ASSEMBLY CODE ----" << endl;
        
        
        
        
        gen.preOutputAssemblyStr("Reza", cout);
        
        gen.outputAssemblyStrIntLiterals("Reza", cout);
        gen.outputAssemblyStrIntLiterals("Daniel", cout);
        gen.outputAssemblyStrIntLiterals("Folsom", cout);
        gen.outputAssemblyStrIntLiterals("Morris", cout);
        
        
        
        
	// gen.generateAssembly(cout);

        
        
	gen.outputAssemblyInt32IntLiterals("3", cout);
	gen.outputAssemblyInt32IntLiterals("6", cout);
	gen.outputAssemblyInt32IntLiterals("2", cout);
	gen.outputAssemblyInt32IntLiterals("123", cout);
	gen.outputAssemblyInt32IntLiterals("90", cout);
        

    return 0;
}
