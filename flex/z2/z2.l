%{
#include "defs.h"
%}

%%
\<\?xml.*\?\> return xml;

\<!-- return comment_begin;
-- return comment_invalid;
--\> return comment_end;

\" return quote_double;
' return quote_single;
\\\"|\\' return raw;

\<!\[CDATA\[ return data_begin;
\]\]> return data_end;

.|\n return raw;
%%