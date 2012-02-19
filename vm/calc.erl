-module(calc).
-export([rpn/1]).
 
rpn(L) when is_list(L) ->
	[Res] = lists:foldl(fun rpn/2, [], string:tokens(L, " ")),
	Res.

read(N) ->
	case string:to_float(N) of
		{error,no_float} -> list_to_integer(N);
		{F,_} -> F
	end.

rpn("+", [N1,N2|S]) -> [N2+N1|S];
rpn("sum", [N]) -> [N];
rpn("sum", [N1, N2|S]) -> rpn("sum", [N1+N2|S]);
rpn("prod", Stack) -> [lists:foldl1(fun(N, R) -> N * R end, 1, Stack)];
rpn(X, Stack) -> [read(X)|Stack].