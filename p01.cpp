//----------------------------------------------------------------------
// File p01.cpp processes command line arguments and invokes lex
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
// Project Account Number:	tt036
//----------------------------------------------------------------------
//C++ include files
//----------------------------------------------------------------------
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <iomanip>
using namespace std;

//----------------------------------------------------------------------
//Application include files
//-----------------------------------------------------------------------
#include "p01lex.h"

//-----------------------------------------------------------------------
//FileException is thrown when a file whose name is given on the command line
//cannot be opened.
//-----------------------------------------------------------------------
struct FileException {
	FileException(const char* fn) 
	{ 
		cout << endl;
		cout << "File " << fn << " cannot be opened.";
		cout << endl;
	}
};

//-----------------------------------------------------------------------
//ExtenstionException is thrown when an input file has the incorrect
//extenstion.
//-----------------------------------------------------------------------
struct ExtensionException {

	ExtensionException(const char* fn, const char* ext){

		cout << endl;
		cout << "File " << fn << " has an incorrect extension.";
		cout << endl;
		cout << "File should have " << ext << " extenstion.";
		cout << endl;

	}

};

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//Commandlineerror is thrown when too many arguments are put on the
//command line
//-----------------------------------------------------------------------
struct CommandLineException {
	CommandLineException(int m,int a)
	{ 
		cout << endl;
		cout << "Too many file names on the command line.";
		cout << endl;
		cout << "A maximum of " << m << " file names can appear on the command line.";
		cout << endl;

		cout << a << " file names were entered.";
		cout << endl;
		cout << "p01 (<input file name>)";
	}
};

//-----------------------------------------------------------------------
//Function Title prints a title
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
//Function LexMgr processes the input file, calls yylex, the scanner, and
//produces the output file.
//-----------------------------------------------------------------------
void LexMgr(FILE* i,ostream& o)
{ 
	static const char* TokenName[]=
		{"AND", "ARRAY", "BEGAN", "DIV", "DO", "DOWNTO",
		 "ELSE", "END", "FOR", "FUNCTION", "IF", "MOD",
		  "NOT", "OF", "OR", "PROCEDURE", "PROGRAM", 
		  "REPEAT", "THEN", "TO", "UNTIL", "VAR", "WHILE",
		  "EQU", "NEQ", "LES", "LEQ", "GRT", "GEQ", "PLUS",
		  "MINUS", "STAR", "SLASH", "ASSIGN", "LPAREN",
		  "RPAREN", "LBRACKET", "RBRACKET", "LCURLY", "RCURLY",
		  "COLON", "SEMICOLON", "COMMA", "PERIOD", "RANGE",
		  "APOSTROPHE", "ID", "INTLIT", "CHRLIT", "REALIT",
		  "ERROR"};

		Lexer L(i); //Redirect yylex to read file i instead of
		//the command line

		for (int t=yylex();t>0;t=yylex()){
			o << endl;
			o << setw(15) << "Token:"<< "Code= "<< t;
			o << " ";
			o << "Name=" << setw(15) << TokenName[t - 1];
			o << " ";
			o << "Line=" << setw(6) << L.FetchLine();
			o << " ";
			o << "col=" << setw(6) << L.FetchColumn();
			o << " ";
			o << "Spelling="<< '\"' << L.FetchSpelling() << '\"';
		}
	o << endl;
}

//-----------------------------------------------------------------------
//Function main processes command line arguments
//-----------------------------------------------------------------------
int main(int argc, char* argv[])
{ 
	try {
		char ifn[255], ofn[255];
		char validExtension[] = {'.', 'p', 'a', 's', '\0'};
		char outExtension[] = {'.', 't', 'r', 'c', '\0'};
		switch (argc) {
			case 1://no files on the command line
				cout << "Enter the input file name. ";
				cin >> ifn;
				break;
			case 2://input file on the command line/prompt for output file
				strcpy(ifn,argv[1]);
				break;
			default:
				throw CommandLineException(1,argc-1);
				break;
		}
		int strLen = strlen(ifn);
		if(strLen < 4){
			throw ExtensionException(ifn, validExtension);
		}
		for(int i = 0; i < 4; i++){
			if(ifn[strLen - 4 + i] != validExtension[i]){
				throw ExtensionException(ifn, validExtension);
			}
		}
		FILE* i=fopen(ifn,"r"); if (!i) throw FileException(ifn);
		strcpy(ofn, ifn);
		ofn[strLen - 4] = '\0';
		strcat(ofn, outExtension);
		ofstream o(ofn); if (!o) throw FileException(ofn);
		LexMgr(i,o);
		fclose(i);
		o.close();
	} catch ( ... ) {
		cout << endl;
		cout << "Program Terminated!";
		cout << endl;
		cout << "I won't be back!";
		cout << endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}