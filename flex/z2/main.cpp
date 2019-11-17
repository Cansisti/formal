#include <iostream>
#include <string>

#include "defs.h"

extern char* yytext;
extern int yylex();

using namespace std;

int main() {

	State state = normal;
	Detection detection;
	string buffer;
	bool xml_detected = false;
	
	while((detection = Detection(yylex())) != nothing) {
		cerr << state << " " << detection << "\t\t" << yytext << endl;
		switch(state) {
			case normal: {
				switch(detection) {
					case xml: {
						xml_detected = true;
						break;
					}
					case comment_begin: {
						buffer = yytext;
						state = comment;
						continue;
					}
					case quote_single: {
						state = string_single;
						break;
					}
					case quote_double: {
						state = string_double;
						break;
					}
					case data_begin: {
						state = data;
						break;
					}
				}
				break;
			}
			case comment: {
				switch(detection) {
					case comment_end: {
						state = normal;
						continue;
					}
					case comment_invalid: {
						cout << buffer;
						state = normal;
						break;
					}
					default: {
						buffer += yytext;
						continue;
					}
				}
				break;
			}
			case string_single: {
				switch(detection) {
					case quote_single: {
						state = normal;
						break;
					}
				}
				break;
			}
			case string_double: {
				switch(detection) {
					case quote_double: {
						state = normal;
						break;
					}
				}
				break;
			}
			case data: {
				switch(detection) {
					case data_end: {
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