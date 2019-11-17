#include <iostream>

using namespace std;

void baz() {
	cout << "baz" << endl;
}

void foo() {
	cout << "foo" << endl;
}

int main() {
	//*/ bar();

    // \
    /*
    baz();
    /*/
    foo();
    //*/

/\
/*
    baz();
/*/
    foo();
//*/
	return 0;
}