#include "calc.h"

void Calc::evaluate(Symbol symbol) {
	switch(symbol.detection) {
		case number: {
			cerr << "num: " << stoi(symbol.raw) << endl;
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
			if(args[0] == 0) throw string("Error: division by 0");
			data.push(args[1] / args[0]);
			break;
		}
		case opow: {
			auto args = pop<2>();
			data.push(std::pow(args[1], args[0]));
			break;
		}
		case omod: {
			auto args = pop<2>();
			if(args[0] == 0) throw string("Error: division by 0");
			data.push(args[1] % args[0]);
			break;
		}
		default: {
			throw string("Error: unknown symbol: " + symbol.raw);
		}
	}
	cerr << "top: " << data.top() << endl;
}

int Calc::result() {
	if(data.size() != 1) throw string("Error: incomplete calculation");
	int r = data.top();
	data.pop();
	return r;
}

void Calc::clear() {
	while(!data.empty()) data.pop();
}