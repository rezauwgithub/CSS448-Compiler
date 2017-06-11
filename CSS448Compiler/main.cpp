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
        
        
        
        
        cout << "\tload_label " << 
                gen.generateAssemblyCodeForStringIntL("Hi Reza! You are the shit today!");// returns label
         
        
        cout << "\n\tload_label printString";
        cout << "\n\tcall\n\n";

        
        cout << "\tload_label " << 
                gen.generateAssemblyCodeForStringIntL("6pm? Or tomorrow 10am? 10am!!!! Please!");// returns label
        
        cout << "\n\tload_label printString";
        cout << "\n\tcall\n\n";
        
        
        
        cout << "\tload_label done\n";
        cout << "\tbranch\n";
        
        cout << "\n\n";
        
        
        cout << gen.generateAssemblyCodeForStringLoop();        // returns loop
        
        cout << "\n\n";
        
        
        cout << gen.generateAssemblyCodeForStringDone();        // returns done
        
        
        cout << "\n\n";
        
        
        cout << gen.getAssemblyCodeForAllStringsIntL();         // returns allStrings
        
        
        cout << "\n\n";
        
        
	// gen.generateAssembly(cout);

	//gen.declareInt32("3");
	//gen.declareInt32("6");
	//gen.declareInt32("2");
	//gen.declareInt32("123");
	//gen.declareInt32("90");
	//gen.generateDeclaredInt32s();

    return 0;
}
