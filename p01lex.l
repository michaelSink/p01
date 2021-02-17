%option noyywrap
%{
//----------------------------------------------------------------------
// File p01lex.l defines a prototype scanner for the micro language.
// The scanner definition is a lex specification
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
// Standard C and C++ include files
//--------------------------------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <string.h>
//--------------------------------------------------------------------
// Application Includes
//--------------------------------------------------------------------
#include "p01lex.h"
//--------------------------------------------------------------------
//Token definitions
//--------------------------------------------------------------------
#include "p01tkn.h"
//--------------------------------------------------------------------
//Namespaces
//--------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------
//Externals
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//Global Variables
//--------------------------------------------------------------------
int lineNumber = 1;
int aCol = 0;
bool first = true;
int columnNumber = 1;
int TokenMgr(int t); //Token post processing
%}
%%
\n					{lineNumber++; columnNumber = 1; first = true;}
[ \t]+                              {aCol += 1;}
[{][^{]*[}]				;//allow for scanner to ignore comments
[aA][nN][dD]	return TokenMgr(AND);
[aA][rR]{2}[yY]	return TokenMgr(ARRAY);
[bB][eE][gG][iI][nN]	return TokenMgr(BEGAN);
[dD][iI][vV]	return TokenMgr(DIV);
[dD][oO]	return TokenMgr(DO);
[dD][oO][wW][nN][tT][oO]	return TokenMgr(DOWNTO);
[eE][lL][sS][eE]	return TokenMgr(ELSE);
[eE][nN][dD]	return TokenMgr(END);
[fF][oO][rR]	return TokenMgr(FOR);
[fF][uU][nN][cC][tT][iI][oO][nN]	return TokenMgr(FUNCTION);
[iI][fF]	return TokenMgr(IF);
[mM][oO][dD]	return TokenMgr(MOD);
[nN][oO][tT]	return TokenMgr(NOT);
[oO][fF]	return TokenMgr(OF);
[oO][rR]	return TokenMgr(OR);
[pP][rR][oO][cC][eE][dD][uU][rR][eE]	return TokenMgr(PROCEDURE);
[pP][rR][oO][gG][rR][aA][mM]	return TokenMgr(PROGRAM);
[rR][eE][pP][eE][aA][tT]	return TokenMgr(REPEAT);
[tT][hH][eE][nN]	return TokenMgr(THEN);
[tT][oO]	return TokenMgr(TO);
[uU][nN][tT][iI][lL]	return TokenMgr(UNTIL);
[vV][aA][rR]	return TokenMgr(VAR);
[wW][hH][iI][lL][eE]	return TokenMgr(WHILE);
[0-9]+                                  return TokenMgr(INTLIT);
[0-9]+[eE][+|-]?[0-9]+					return TokenMgr(REALIT);
[0-9]+[.][0-9]+[eE][+|-]?[0-9]+			return TokenMgr(REALIT);
[0-9]+[.][0-9]+							return TokenMgr(REALIT);
['][^ \t\n\{]+[']						return TokenMgr(CHRLIT);
[_a-zA-Z][_a-zA-Z0-9]* return TokenMgr(ID);
"="		return TokenMgr(EQU);
"<>"	return TokenMgr(NEQ);
"<"		return TokenMgr(LES);
"<="	return TokenMgr(LEQ);
">"		return TokenMgr(GRT);
">="	return TokenMgr(GEQ);
"+"		return TokenMgr(PLUS);
"-"		return TokenMgr(MINUS);
"*"		return TokenMgr(STAR);
"/"		return TokenMgr(SLASH);
":="	return TokenMgr(ASSIGN);
"("		return TokenMgr(LPAREN);
")"		return TokenMgr(RPAREN);
"["		return TokenMgr(LBRACKET);
"]"		return TokenMgr(RBRACKET);
"{"		return TokenMgr(LCURLY);
"}"		return TokenMgr(RCURLY);
":"		return TokenMgr(COLON);
";"		return TokenMgr(SEMICOLON);
","		return TokenMgr(COMMA);
"."		return TokenMgr(PERIOD);
".."	return TokenMgr(RANGE);
"'"		return TokenMgr(APOSTROPHE);
.       return TokenMgr(ERROR);
%%
//--------------------------------------------------------------------
//Class Lexer implementation
//--------------------------------------------------------------------
//Function TokenMgr processes the token after it has been recognized
//--------------------------------------------------------------------
int TokenMgr(int t)
{

	columnNumber += aCol;
	aCol = strlen(yytext);

	return t;
}
//--------------------------------------------------------------------
//Constructor Lexer is used to redirect the input file stream from the
//keyboard to input file stream i.
//--------------------------------------------------------------------
Lexer::Lexer(FILE* i)
{ yyin=i;
}
//--------------------------------------------------------------------
//Function Lex calls yylex
//--------------------------------------------------------------------
int Lexer::Lex(void)
{ tokencode=yylex();
 return tokencode;
}
//--------------------------------------------------------------------
//Function FetchSpelling returns a pointer to the spelling of the most
//recent token.
//--------------------------------------------------------------------
char* Lexer::FetchSpelling(void)
{
 return (char*)yytext;
}
//--------------------------------------------------------------------
//Function FetchTokenCode returns the code of the most recent token
//--------------------------------------------------------------------
int Lexer::FetchTokenCode(void)
{ return tokencode;
}
//--------------------------------------------------------------------
//Function FetchLine returns the current line stored in lineNumber
//--------------------------------------------------------------------
int Lexer::FetchLine(void)
{ return lineNumber;
}
//--------------------------------------------------------------------
//Function FetchColumn returns the current column stored in columnNumber
//--------------------------------------------------------------------
int Lexer::FetchColumn(void)
{ return columnNumber;
}
//--------------------------------------------------------------------
//Function StoreTokenCode records the most recent token code
//--------------------------------------------------------------------
void Lexer::StoreTokenCode(int T)
{ tokencode=T;
}
//-----------------------End of Lex Definition------------------------