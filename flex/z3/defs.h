#pragma once

enum State {
	normal,
	block_comment,
	line_comment,
	inside_string,
	doxy_line,
	doxy_block,
	immune
};

enum Detection {
	nothing,
	raw,
	br,
	not_br, // coz y use one

	line_comment_begin,
	block_comment_begin,
	block_comment_end,
	doxy_line_begin,
	doxy_block_begin,

	quote,
	immunity
};