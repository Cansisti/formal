#pragma once
#include <string>

enum Detection {
	nothing,
	skip,
	error,

	number,
	oadd,
	osub,
	omul,
	odiv,
	opow,
	omod,
	onegate,

	enter
};

struct Symbol {
	Detection detection;
	std::string raw;
};