%{
#include <iostream>
#include "defs.h"
#include "calc.h"
#define YYSTYPE std::string

extern int yylex();
extern void yyerror(const char*);
extern char* yytext;

Calc calc;
Detection detection = skip;
extern int yylineno;
%}
%define api.value.type {std::string};

%token N "number"

%token PLU "+"
%token MIN "-"
%token MUL "*"
%token DIV "/"
%token POW "^"
%token MOD "modulo"
%token BR_O "("
%token BR_C ")"

%token END
%token ERR

%%

input:	| input line | input ERR {
	calc.clear();
};
line:	s END {
	std::cout << $1 << std::endl;
	std::cout << "= " << calc.result() << std::endl;
};

s: i | ii | iii;
i: a | b;
ii: c | d | iii;
iii: e | f;

a: s PLU s {
	$$ = $1 + " " + $3 + " +";
	calc.evaluate({oadd, $2});
};
b: s MIN ii {
	$$ = $1 + " " + $3 + " -";
	calc.evaluate({osub, $2});
};
c: ii MUL ii {
	$$ = $1 + " " + $3 + " *";
	calc.evaluate({omul, $2});
};
d: ii DIV iii {
	$$ = $1 + " " + $3 + " /";
	calc.evaluate({odiv, $2});
}| ii MOD iii {
	$$ = $1 + " " + $3 + " %";
	calc.evaluate({omod, $2});
};
f: e POW iii {
	$$ = $1 + " " + $3 + " ^";
	calc.evaluate({opow, $2});
};

e: BR_O s BR_C {
	$$ = $2;
}| N {
	$$ = $1;
	calc.evaluate({number, $1});
}| MIN e {
	$$ = "-" + $2;
	// $$ = "0 " + $2 + " -";
	calc.evaluate({onegate, $1});
};

%%

void yyerror(const char* err) {
	std::cout << yylineno - 1 << ": " << err << std::endl;
	calc.clear();
}