#include "calc.h"

#define STRANGE_MODULO

#define abs(x) (x) < 0 ? -(x) : (x)

void Calc::evaluate(Symbol symbol) {
	switch(symbol.detection) {
		case number: {
			data.push(stoi(symbol.raw));
			break;
		}
		case oadd: {
			auto args = pop<2>();
			data.push(args[1] + args[0]);
			break;
		}
		case osub: {
			auto args = pop<2>();
			data.push(args[1] - args[0]);
			break;
		}
		case omul: {
			auto args = pop<2>();
			data.push(args[1] * args[0]);
			break;
		}
		case odiv: {
			auto args = pop<2>();
			int r = args[1] / args[0];
			if(r < 0) {
				r -= abs(args[1] % args[0]);
			}
			if(args[0] == 0) throw runtime_error("Error: division by 0");
			data.push(r);
			break;
		}
		case opow: {
			auto args = pop<2>();
			data.push(std::pow(args[1], args[0]));
			break;
		}
		case omod: {
			auto args = pop<2>();
			if(args[0] == 0) throw runtime_error("Error: division by 0");
			int r = args[1] % args[0];
			#ifdef STRANGE_MODULO
			while(r * args[0] < 0) r += args[0];
			#endif
			data.push(r);
			break;
		}
		case onegate: {
			auto args = pop<1>();
			data.push(-args[0]);
			break;
		}
		default: {
			throw runtime_error("Error: unknown symbol: " + symbol.raw);
		}
	}
	cerr << "top: " << data.top() << endl;
}

int Calc::result() {
	if(data.size() != 1) throw runtime_error("Error: incomplete calculation");
	int r = data.top();
	data.pop();
	clear();
	return r;
}

void Calc::clear() {
	while(!data.empty()) data.pop();
}