template <class Typelist, class T, class U> class Replace;

template <class T, class U> Replace<NullType, T, U>
{
	typedef NullType result;
};

template<class Typelist, class T> class Replace<Typelist, T, NullType>
{
	typedef Erase<Typelist, T>::result result;
}

template<class T, class Tail, class U> class Replace<Typelist<T, Tail>, T, U>
{
	typedef Typelist<U, Tail> result;
};

template<class Head, class Tail, class T, class U> class Replace<Typelist<Head, Tail>, T, U>
{
	typedef Typelist<Head, typename Replace<Tail, T, U> > result;
};
