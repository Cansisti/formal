%{
#include <iostream>
#include <string>
using namespace std;

int line_count = 0;
int word_count = 0;
bool fwnl = false;

bool blank_state = false;
%}

%%

^\n {
	blank_state = false;
	fwnl = false;
}

\n {
	blank_state = false;
	line_count++;
	fwnl = true;
	cout << endl;
}

^[[:blank:]]+ {
	blank_state = false;
	fwnl = false;
}

^[[:blank:]]*\n {
	fwnl = false;
	blank_state = false;
}

[[:blank:]] {
	blank_state = true;
}

[^ \t\n]+ {
	if(blank_state) cout << " ";
	cout << yytext;
	blank_state = false;
	word_count++;
	fwnl = false;
}

%%

int main() {
	yylex();
	if(!fwnl) line_count++;
	cerr << line_count << " " << word_count << endl;
	return 0;
} 
