#include <iostream>
#include "calc.h"

extern int yyparse();

using namespace std;

int main() {
	while(true) yyparse();
	return 0;
}