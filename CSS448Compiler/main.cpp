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
    return 0;
}
