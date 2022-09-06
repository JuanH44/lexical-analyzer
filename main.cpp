#include <iostream>
#include <stdlib.h>

using namespace std;

class Token {
	public:
		char name;
		char attrib;

		Token(char nombre, char atributo) {
			this->name = nombre;
			this->attrib = atributo;
		}
};

int main(int argc, char const *argv[]){

	Token tk = Token('a', 'b');
	
	cout << tk.name << endl;
	cout << tk.attrib << endl;

	return 0;
};


Token getToken(){
	Token tk = Token('a', 'b');
	return tk;
}