#include<iostream>
#include <variant>
#include "InfinitePrecision.h"

using namespace std;
using namespace InfinitePrecision;

int main(int argc, char* argv[]) {
    if (argc < 5) {
            cerr << "usage: my_inf_arith <int,float> <add,sub,mul,div> n1 n2" << endl;
            return 1;
    }
    string dtype=argv[1];
    string operation=argv[2];
    string n1=argv[3];
    string n2=argv[4];
    if (dtype == "int") {
        Integer num1(n1);
        Integer num2(n2);
        if (operation == "add") {
            cout << num1+num2 << endl;
        }
	else if (operation == "sub") {
		cout << num1-num2 << endl;
	}
	else if (operation == "mul") {
		cout << num1*num2 << endl;
	}
	else if (operation == "div") {
		cout << num1/num2 << endl;
	}
        else {
            cout << "argument2 must be an operation <add,sub,mul,div>" << endl;
            return 1;
        }
    }
    else if (dtype == "float") {
        Float num1(n1);
        Float num2(n2);
        if (operation == "add") {
            cout << num1+num2 << endl;
        }
	 else if (operation == "sub") {
                cout << num1-num2 << endl;
        }
        else if (operation == "mul") {
                cout << num1*num2 << endl;
        }
        else if (operation == "div") {
                cout << num1/num2 << endl;
        }
        else {
            cout << "argument2 must be an operation <add,sub,mul,div>" << endl;
            return 1;
        }
    }
    else {
        cerr << "error: argument1 must be int or float" << endl;
        return 1;
    }

}
