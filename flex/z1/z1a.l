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
^[[:blank:]]*\n {
	cerr << 0 << endl;
	// line_count++;
	fwnl = true;
}
\n {
	cerr << 1 << endl;
	cout << endl;
	line_count++;
	fwnl = true;
}
^[[:blank:]]+ {
	cerr << 2 << endl;
	fwnl = false;
}
[[:blank:]]+\n$ {
	line_count++;
	cerr << -3 << endl;
	fwnl = true;
}
[[:blank:]]+\n {
	cerr << 3 << endl;
	cout << "\n";
	line_count++;
	fwnl = true;
}
[[:blank:]]+ {
	cerr << 5 << endl;
	cout << " ";
	fwnl = false;
}
[^ \t\n]+ {
	cerr << 6 << endl;
	cout << yytext;
	word_count++;
	fwnl = false;
}

[[:blank:]] {
	blank_state = true;
	fwnl = false;
}

%%

int main() {
	yylex();
	if(!fwnl) line_count++;
	cerr << line_count << " " << word_count << endl;
	return 0;
} 
