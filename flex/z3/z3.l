%{
#include "defs.h"
%}

hacks (\\[:blank:]*\n)*

%%

\" return quote;

#include return immunity;

\/{hacks}\*{hacks}\* return doxy_block_begin;
\/{hacks}\*{hacks}! return doxy_block_begin;
\/{hacks}\/{hacks}\/ return doxy_line_begin;
\/{hacks}\/{hacks}! return doxy_line_begin;

\/{hacks}\* return block_comment_begin;
\*{hacks}\/ return block_comment_end;

\/{hacks}\/ return line_comment_begin;

\\[:blank:]*\n return not_br;
. return raw;
\n return br;

%%