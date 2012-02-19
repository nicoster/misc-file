-module(recursive).
-export([lenient_zip/2]).

lenient_zip(X, Y) -> lists:reverse(lenient_zip(X, Y, [])).

lenient_zip([], _, Acc) -> Acc;
lenient_zip(_, [], Acc) -> Acc;
lenient_zip([X|Xs], [Y|Ys], Acc) -> lenient_zip(Xs, Ys, [{X, Y}|Acc]).