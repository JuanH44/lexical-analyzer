#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

void nextChar(char ** charArray){
	(*charArray)++;
}

void backtrack(char ** charArray){
	(*charArray)--;
}

class Token {
	public:
		string name;
		string attrib;

		Token(string nombre, string atributo) {
			this->name = nombre;
			this->attrib = atributo;
		}
		Token(string name) {
			this->name = name;
		}
};

Token getRelationalOperator(char ** input){
	char * index1 = *input, *index2 = *input;
	char c; 
	Token tk = Token("RelOp");
	int state = 0;

	while (true){
		switch (state){
			case 0:
				c = *input[0];
				//cout << "c: " << c << endl;
				nextChar(input);
				
				if (c == '<'){
					state = 1;
				} else if (c == '='){
					state = 5;
				} else if (c == '>'){
					state = 6;
				} else {
					tk.name = "ERROR";
					cout<<"Not a RelOP"<<endl; //pending function
					return tk;
				}
				break;
			case 1:
				c = *input[0];
				nextChar(input);
				if (c == '='){
					state = 2;
				} else if(c == '>'){
					state = 3;
				} else {
					state = 4;
				}
				break;
			case 2:
				cout << string(index1, *input) << endl;
				tk.attrib = "LE";

				return tk;
				break;
			case 3:
				cout << string(index1, *input) << endl;
				tk.attrib = "NE";
				return tk;
				break;
			case 4:
				cout << string(index1, *input) << endl;
				tk.attrib = "LT";
				return tk;
				break;
			case 5:
				cout << string(index1, *input) << endl;
				tk.attrib = "EQ";
				return tk;
				break;
			case 6:
				c = *input[0];
				nextChar(input);
				if (c == '='){
					state = 7;
				} else {
					state = 8;
				}
				break;
			case 7:
				cout << string(index1, *input) << endl;
				tk.attrib = "GE";
				return tk;
				break;
			case 8:
				backtrack(input);
				cout << string(index1, *input) << endl;
				tk.attrib = "GT";
				return tk;
				break;
		}
	}
	
}


void fail(Token tk){
	tk.name = "FAIL";
}


void getTokens(string stringToProcess){


	char * charArray = new char [stringToProcess.length() + 1];
	strcpy(charArray, stringToProcess.c_str());

	char * stringStart =  charArray;
	char * tokenStart;
	int i = 0;
	while (*charArray != '\0' && i < 50){
		tokenStart = charArray;
		//cout << "s: " << charArray << endl;

		Token tk = getRelationalOperator(&charArray);
		if(tk.name == "RelOp"){
			cout<<tk.name <<" : "<<tk.attrib<<endl;
		} else {
			//cout<<"fail e"<<endl;

			// charArray = tokenStart; //try with other method
		}
		nextChar(&charArray);
		i++;
	}
}

int main(int argc, char const *argv[]){
	string h ("<=11 <>5>=10 ");
	
	getTokens(h);

	cout << "End of program" << endl;
		
	return 0;
}



