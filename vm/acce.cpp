struct Empty{};
	
template<typename Left, typename Right = Left>
struct Accelerate{
    Left& left;
    Right& right;
	
	operator string () const{
		string str;
		str.reserve(length(left) + length(right));
		append(str, left);
		append(str, right);
		return str;
	};
	
};

template<typename T>
inline size_t length(const T& t){
            return t.size();
}

template<typename Left, typename Right>
inline size_t length(const Accelerate<Left, Right>& t){
	return length(t.left) + length(t.right);
}

template<>
inline size_t length(const Accelerate<Empty, Empty>& t){
	return 0;
}

template<typename Left, typename Right>
inline append(string& str, const Accelerate& t ){
	append(str, t.left);
	append(str,t.right);
}

template< >
inline append(string&, const Accelerate<Empty, Empty>& ){}

template< >
inline append(string& str, const string& rsh){
	copy(rsh.begin(), rsh.end(), back_inserter(str));
}

template<typename Left, typename Right>
inline Accelerate< Accelerate< Left >, Right> 
operator+(Accelerate< Left >& lsh, const Right& rsh)
{
	return Accelerate< Accelerate< Left >, Right>(lsh, rsh);
}

typedef Accelerate<Empty, Empty> Acce;

Acce() + str_you + ¡°said: ¡± + str_he + ¡° said: @#$% ¡± + str_i + ¡°said: over!¡±;