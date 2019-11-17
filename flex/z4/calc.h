#include <stack>
#include <string>
#include <array>
#include <math.h>
#include <iostream>
#include "defs.h"

using namespace std;

class Calc {
	private:
		stack<int> data;

		template<size_t num>
		array<int, num> pop() {
			array<int, num> ret;
			if(data.size() < num) throw string("Error: not enought data to perform operation");
			for(size_t i = 0; i<num; i++) {
				ret[i] = data.top();
				data.pop();
			}
			return ret;
		}
	public:
		void evaluate(Symbol symbol);
		int result();
		void clear();
};