%{
#include <iostream>
#include <string>
using namespace std;

int line_count = 0;
int word_count = 0;
%}

%% 
^[[:blank:]]*\n {
	line_count++;
}
\n {
	cout << endl;
	line_count++;
}
^[[:blank:]]+ {
}
[[:blank:]]+$ {
}
[[:blank:]]+ {
	cout << " ";
}
[^ \t\n]+ {
	cout << yytext;
	word_count++;
}
%% 

int main() {
	yylex();
	// cout << line_count << " " << word_count << endl;
	return 0;
} 
