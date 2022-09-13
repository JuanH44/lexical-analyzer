#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cstring>
// #include "tokenIdentifiers.h"

using namespace std;

class Token {
	public:
		string name;
		string attrib;

		Token(string name) {
			this->name = name;
		}

		Token(string nombre, string atributo) {
			this->name = nombre;
			this->attrib = atributo;
		}
};


//Function declarations
void getTokens(string stringToProcess);  //Prints the tokens, but in the future it should return a list of tokens
Token getRelationalOperator(char ** input);
char * convertToCharArray(string stringToProcess);
char nextChar(char ** charArray);
void backtrack(char ** charArray);
void fail(Token tk);
void printPointer(string name, char * pointer);

int main(int argc, char const *argv[]){
	string h ("9<=67 <>5 >=1 >aa=7 6 <");
	
	getTokens(h);

	cout << "End of program" << endl;
		
	return 0;
}

//Identify the token type
void getTokens(string stringToProcess){

	char * startOfString = convertToCharArray(stringToProcess);
	char * index = startOfString;
	char * startOfToken;
	int i = 0;
	while (*index != '\0' && i < 50){ // i avoids infinite loop
		char * startOfToken;
		//cout << "s: " << index << endl;

		Token tk = getRelationalOperator(&index);
		if(tk.name == "RelOp"){
			//cout<<tk.name <<" : "<<tk.attrib<<endl;
		} else {
		//	nextChar(&index);  // this will be removed when the other token identifiers are implemented
		}
		i++;
	}
}

Token getRelationalOperator(char ** input){
	char * startOfToken = (*input)+1;
	char ** index = input;
	//backtrack(index);  //This is needed because the nextChar function increments the pointer in the state 0
	
	char c; 
	Token tk = Token("RelOp");
	int state = 0;

	while (tk.attrib == ""){
		switch (state){
			case 0:
				c = nextChar(index);		
				if (c == '<'){
					state = 1;
				} else if (c == '='){
					state = 5;
				} else if (c == '>'){
					state = 6;
				} else {	
					tk.name = "Fail";
					tk.attrib = "NRO"; //Not a RelOp
					//backtrack(index);  //Uncomment this when the other token identifiers are implemented
				}
				break;
			case 1:
				c = nextChar(index);		
				if (c == '='){
					state = 2;
				} else if(c == '>'){
					state = 3;
				} else {
					state = 4;
				}
				break;
			case 2:
				tk.attrib = "LE";
				break;
			case 3:
				tk.attrib = "NE";
				break;
			case 4:
				backtrack(index);
				tk.attrib = "LT";
				break;
			case 5:
				tk.attrib = "EQ";
				break;
			case 6:
				c = nextChar(index);		
				if (c == '='){
					state = 7;
				} else {
					state = 8;
				}
				break;
			case 7:
				tk.attrib = "GE";
				break;
			case 8:
				backtrack(index);
				tk.attrib = "GT";
				break;
		}
	}
	cout<<string(startOfToken, *index+1)<< "\t "<< tk.name <<" - "<<tk.attrib<<endl; 
	return tk;
}

char nextChar(char ** charArray){
	(*charArray)++;
	return *charArray[0];
}

char * convertToCharArray( string stringToProcess){
	stringToProcess = " " + stringToProcess; //It is needed because the first character is ignored by the automaton
	char * charArray = new char [stringToProcess.length() + 1];
	strcpy(charArray, stringToProcess.c_str());
	return charArray;
}

void backtrack(char ** charArray){
	(*charArray)--;
}
