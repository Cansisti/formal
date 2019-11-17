%{
#include "defs.h"
%}

%%
\+ return oadd;
- return osub;
\* return omul;
\/ return odiv;
\^ return opow;
% return omod;

[[:blank:]]+ return skip;
[\-0-9]+ return number;

\n return enter;
. return error;
%%