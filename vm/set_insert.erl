-module(set_insert).
-export([insert/2, help_me/1, help_me2/1]).

insert(X, []) ->
	[X];
	
%insert(X, Set) when lists:member(X, Set)  ->
%	Set;
	
%insert(X, Set) ->
%	[X|Set].

insert(X,Set) ->
	case lists:member(X,Set) of
		true  -> Set;
		false -> [X|Set]
	end.	

help_me(Animal) ->
	Talk = case Animal of
		cat -> "meow";
		beef -> "mooo";
		_ -> "_"
	end,
	{Animal, "Says " ++ Talk ++ "!"}.
	

help_me2(cat) ->
	{cat, "Says meow!"};
help_me2(beef) ->
	{beef, "Says mooo!"};
help_me2(_) ->
	{ "Says _!"}.