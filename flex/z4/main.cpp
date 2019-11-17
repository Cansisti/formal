#include <iostream>
#include <string>

#include "defs.h"
#include "calc.h"

extern char* yytext;
extern int yylex();

using namespace std;

int main(int argc, char** argv) {

	Calc calc;
	Detection detection = skip;

	while((detection = Detection(yylex())) != nothing) {
		cerr << detection << " (" << yytext << ")" << endl;
		try {
			if(detection == enter) {
				int r = calc.result();
				cout << "= " << r << endl;
				calc.clear();
			}
			else {
				if(detection == nothing) break;
				if(detection == skip) continue;
				calc.evaluate({detection, yytext});
			}
		}
		catch(string ex) {
			calc.clear();
			cout << ex << endl;
			while(detection != enter) detection = Detection(yylex());
			cerr << endl;
		}
	}

	return 0;
}