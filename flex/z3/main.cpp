#include <iostream>
#include <string>

#include "defs.h"

// https://gcc.gnu.org/onlinedocs/gcc-3.2/cpp/Initial-processing.html

extern char* yytext;
extern int yylex();

using namespace std;

int main(int argc, char** argv) {


	State state = normal;
	Detection detection;
	size_t line = 0;
	bool doxything = false;

	if(argc > 1 && string(argv[1]) == "-d") doxything = true;

	while((detection = Detection(yylex())) != nothing) {
		if(detection == br || detection == not_br) line++;
		cerr << "(" << line << ") " << state << " " << detection << "\t\t" << yytext << endl;

		if(!doxything) {
			if(detection == doxy_line_begin) detection = line_comment_begin;
			if(detection == doxy_block_begin) detection = block_comment_begin;
		}

		switch(state) {
			case normal: {
				switch(detection) {
					case line_comment_begin: {
						state = line_comment;
						continue;
					}
					case block_comment_begin: {
						state = block_comment;
						continue;
					}
					case quote: {
						state = inside_string;
						break;
					}
					case immunity: {
						state = immune;
						break;
					}
				}
				break;
			}
			case block_comment: {
				switch(detection) {
					case block_comment_end: {
						state = normal;
						cout << " ";
						continue;
					}
					default: {
						continue;
					}
				}
				break;
			}
			case line_comment: {
				switch(detection) {
					case br: {
						cout << " \n";
						state = normal;
						continue;
					}
					default: {
						continue;
					}
				}
				break;
			}
			case inside_string: {
				switch(detection) {
					case quote: {
						state = normal;
						break;
					}
				}
				break;
			}
			case doxy_line: {
				switch (detection) {
					case br: {
						state = normal;
						break;
					}
				}
				break;
			}
			case doxy_block: {
				switch(detection) {
					case block_comment_end: {
						state = normal;
						break;
					}
				}
				break;
			}
			case immune: {
				switch(detection) {
					case br: {
						state = normal;
						break;
					}
				}
				break;
			}
		}
		cout << yytext;
	}

	return 0;
}