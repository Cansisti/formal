%option yylineno
%option nounput
%{
#include <iostream>
#include <string>
#include "math.tab.h"

%}

%%
#(.|\\\n)*\n ;
[ \t]+ ;
[0-9]+ { yylval = yytext; return N; }
\+ { yylval = yytext; return PLU; }
- { yylval = yytext; return MIN; }
\* { yylval = yytext; return MUL; }
\/ { yylval = yytext; return DIV; }
% { yylval = yytext; return MOD; }
\( { yylval = yytext; return BR_O; }
\) { yylval = yytext; return BR_C; }
\n { yylval = yytext; return END; }
\^ { yylval = yytext; return POW; }
\\\n ;
. return ERR;
