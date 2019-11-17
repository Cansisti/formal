#pragma once

enum State {
	normal,
	comment,
	string_single,
	string_double,
	data
};

enum Detection {
	nothing,
	raw,
	xml,

	comment_begin,
	comment_end,
	comment_invalid,

	quote_single,
	quote_double,

	data_begin,
	data_end
};