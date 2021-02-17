#ifndef p01lex_h
#define p01lex_h 1

//----------------------------------------------------------------------
// File p01lex.h defines the lexer class
//----------------------------------------------------------------------
// Author 1:				Michael Sinkankas
// Student ID:				*20474232
// E-Mail:					msinkankas@uco.edu
// Student 1 CRN:			22752, Spring, 2021
// Author 2:				Sean Wall
// Student ID:				*20410656
// E-Mail:					swall6@uco.edu
// Student 2 CRN:			21838, Spring 2021
// Course:					CMSC 4023 – Programming Languages
// Project:					p01
// Due:						February 17, 2021
// Project Account Number:	tt000
//----------------------------------------------------------------------
// Standard C and C++ include files
//--------------------------------------------------------------------
#include <cstdio>
#include <fstream>
#include <iostream>
using namespace std;

#include "p01tkn.h"

#ifdef __cplusplus
extern "C"
#endif
int yylex (void);

//--------------------------------------------------------------------
//Class Lexer defines the attributes of a Scanner
//--------------------------------------------------------------------
class Lexer {
	int tokencode; //Code for the most recent token found
	public:
		Lexer(FILE* i); //Constructor used to redirect the keyboard
		//(stdin) to file i.
		int Lex(void); //Call the scanner yylex and return the code
		//found by yylex
		int FetchTokenCode(void); //Return the code of the most recent token
		void StoreTokenCode(int T);//Store the token code.
		char* FetchSpelling(void); //Return the spelling of the most recent
		int FetchLine(void);
		int FetchColumn(void);
 //token
};

#endif