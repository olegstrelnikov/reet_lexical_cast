/*
 * reet_lexical_cast.hpp
 *
 *  Created on: Apr 13, 2017
 *      Author: ois
 */

#ifndef INCLUDE_REET_LEXICAL_CAST_HPP_
#define INCLUDE_REET_LEXICAL_CAST_HPP_

#include <cstddef>
#include <sstream>
#include <locale>

namespace reet {

template <typename T, typename CharT>
T from_istringstream(std::basic_istringstream<CharT>& istream) {
	T t;
	istream >> t;
	return t;
}

template <typename T, typename CharT>
std::basic_string<CharT> to_string(std::basic_ostringstream<CharT>& ostream, T const& from) {
	ostream << from;
	return ostream.str();
}

template <typename T, typename FromT> struct impl {
	static T lexical_cast(FromT const& from);
	static T lexical_cast(FromT const& from, std::locale);
};

//from basic string
template <typename T, typename CharT> struct impl<T, std::basic_string<CharT> > {
	static T lexical_cast(std::basic_string<CharT> const& from) {
		std::basic_istringstream<CharT> iss(from);
		return from_istringstream<T>(iss);
	}
};

//to basic sting
template <typename T, typename FromT> struct impl<std::basic_string<T>, FromT> {
	static std::basic_string<T> lexical_cast(FromT const& from) {
		std::basic_ostringstream<T> oss;
		return to_string(oss, from);
	}
};

//identity
template <typename T> struct impl<T, T> {
	static T lexical_cast(T const& t) {
		return t;
	}
};

template <typename T, typename FromT> T lexical_cast(FromT const& from) {
	return impl<T, FromT>::lexical_cast(from);
}

//from C string
template <typename T, typename FromT> T lexical_cast(FromT const* from) {
	return lexical_cast<T>(std::basic_string<FromT>(from));
}

//from range of characters
template <typename T, typename FromT> T lexical_cast(FromT const* from, std::size_t n) {
	return lexical_cast<T>(std::basic_string<FromT>(from, n));
}

} //namespace reet

#endif /* INCLUDE_REET_LEXICAL_CAST_HPP_ */
