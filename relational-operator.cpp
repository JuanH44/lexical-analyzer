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
Token getBlankSpace(char ** input);
Token getNumber(char ** input);
char * convertToCharArray(string stringToProcess);
char nextChar(char ** charArray);
void backtrack(char ** charArray);
void fail(Token tk);
void printPointer(string name, char * pointer);

int main(int argc, char const *argv[]){
	string h ("9<=67.8 <>5 >=1 >aa=7 6 <");
	
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
		/*if(tk.name == "RelOp"){
			//cout<<tk.name <<" : "<<tk.attrib<<endl;
		} else {
		//	nextChar(&index);  // this will be removed when the other token identifiers are implemented
		}*/
		
		
		Token tk0 = getBlankSpace(&index);
		/*if(tk0.name == "Blank"){
			//cout<<tk0.name <<" : "<<tk0.attrib<<endl;
		} else {
		//	nextChar(&index);  // this will be removed when the other token identifiers are implemented
		}*/
		
		
		Token tk1 = getNumber(&index);
		/*if(tk1.name == "Blank"){
			//cout<<tk1.name <<" : "<<tk1.attrib<<endl;
		} else {
		//	nextChar(&index);  // this will be removed when the other token identifiers are implemented
		}*/
		
		
		i++;
	}
}

Token getRelationalOperator(char ** input){
	char * startOfToken = (*input)+1;
	char ** index = input;
	//backtrack(index);  //This is needed because the nextChar function increments the pointer in the state 0
	//cout<<"\n"<<*index<<endl;	// Remove when done testing
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
	if (tk.attrib != "NRO")
		cout<<string(startOfToken, *index+1)<< "\t "<< tk.name <<" - "<<tk.attrib<<endl;
	return tk;
}

Token getBlankSpace(char ** input){
	char * startOfToken = (*input)-1;
	char ** index = input;
	backtrack(index);  //This is needed because the nextChar function increments the pointer in the state 0
	
	char c;
	Token tk = Token("Blankspace");
	int state = 0;
	
	while (tk.attrib == ""){
		switch (state){
			case 0:
				c = nextChar(index);	// delim could be a blankspace, tab or line feed.
				if (c == 32)
					state = 1;
				else{
					tk.name = "Fail";
					tk.attrib = "NBS";	// Not a Blank Space.
					//backtrack(index);
				}
				break;
			case 1:
				c = nextChar(index);
				if (c == 32)
					state = 1;
				else
					state = 2;
				break;
			case 2:
				backtrack(index);
				tk.attrib = "space";
				break;
		}		
	}
	if (tk.attrib != "NBS")
		cout<<string(startOfToken+1, *index)<< "\t "<< tk.name <<" - "<<tk.attrib<<endl;
	return tk;
}

Token getNumber(char ** input){
	char * startOfToken = (*input);
	char ** index = input;
	backtrack(index);  //This is needed because the nextChar function increments the pointer in the state 0
	
	char c ;
	Token tk = Token("Number");
	int state = 0;
	
	while (tk.attrib == ""){
		switch (state){
			case 0:
				c = nextChar(index);
				if (c >= 48 && c <= 57)
					state = 1;
				else{
					tk.name = "Fail";
					tk.attrib = "NNR";	// Not a Number.
					//backtrack(index);
				}
				break;
			case 1:
				c = nextChar(index);
				if (c >= 48 && c <= 57)
					state = 1;
				else if (c == '.')
					state = 2;
				else if (c == 'E')
					state = 5;
				else
					state = 3;
				break;
			case 2:
				if (c >= 48 && c <= 57)
					state = 4;
				else{	// if the token does not follows the structure of a number, then it is unrecognizable.
					tk.name = "Fail";
					tk.attrib = "NNR";
					//backtrack(index);	
				}
				break;
			case 3:
				backtrack(index);
				tk.attrib = "number";
				break;
			case 4:
				c = nextChar(index);
				if (c >= 48 && c <= 57)
					state = 4;
				else if (c == 'E')
					state = 5;
				else
					state = 6;
				break;
			case 5:
				c = nextChar(index);
				if (c == '+' || c == '-')
					state = 7;
				else if (c >= 48 && c <= 57)
					state = 8;
				else{	// same as case 2.
					tk.name = "Fail";
					tk.attrib = "NNR";
					//backtrack(index);
				}
				break;
			case 6:
				backtrack(index);
				tk.attrib = "number";
				break;
			case 7:
				if (c >= 48 && c <= 57)
					state = 8;
				else{	// same as case 2 and 5.
					tk.name = "Fail";
					tk.attrib = "NNR";
					//backtrack(index);
				}
				break;
			case 8:
				if (c >= 48 && c <= 57)
					state = 8;
				else
					state = 9;
				break;
			case 9:
				backtrack(index);
				tk.attrib = "number";
				break;
		}
	}
	if (tk.attrib != "NNR")
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
