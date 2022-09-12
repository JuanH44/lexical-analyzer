#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

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


Token getRelationalOperator(string c){
	Token tk = Token("RelOp");
	int state = 0;
	switch (state){
		case 0:
			c = c.substr(1);
			if (c == "<"){
				state = 1;
			} else if (c == "="){
				state = 5;
			} else if (c == ">"){
				state = 6;
			} else {
				//fail(); 
				cout<<"fail"<<endl; //pending function
			}
			break;
		case 1:
			c = c.substr(1);
			if (c == "="){
				state = 2;
			} else if(c == ">"){
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
			tk.attrib = "LT";
			break;
		case 5:
			tk.attrib = "EQ";
			break;
		case 6:
			c = c.substr(1);
			if (c == "="){
				state = 7;
			} else {
				state = 8;
			}
			break;
		case 7:
			tk.attrib = "GE";
			break;
		case 8:
			//backtrack();
			tk.attrib = "GT";
			break;
	}
	return tk;
}

int main(int argc, char const *argv[]){
	string h = "Hola mundo";

	cout << "fff" << endl;

	return 0;
}